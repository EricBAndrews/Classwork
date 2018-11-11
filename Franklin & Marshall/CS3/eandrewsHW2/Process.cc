#include "Process.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Process::Process(int id) : id(id) {
    cpuTime = 0;
    waitTime = 0;
}

int Process::getID() const {
    return id;
}

int Process::getCPUTime() const {
    return cpuTime;
}

int Process::getWaitTime(int curCycleNum) const {
    int additionalWait = curCycleNum - lastTime;
    if(additionalWait < 0) {
	additionalWait = 0;
    }
    return waitTime + additionalWait;
}

CPUBoundProcess::CPUBoundProcess(int id) : Process(id) {
    lastTime = 0;
}

bool CPUBoundProcess::isBlocked(int curCycleNum) const {
    return false;
}

int CPUBoundProcess::simulate(int curCycleNum, int sliceSize) {
    /* 
     * updates values of cpuTime, waitTime, and lastTime to reflect the process using all of the
     * CPU time given to it
     */
    cpuTime += sliceSize; // the process uses all CPU time given to it
   
    waitTime += curCycleNum - lastTime;
    // when the process next uses the CPU, it will have been waiting since the end of this
    // window.
    lastTime = curCycleNum + sliceSize;

    return sliceSize;
}

IOBoundProcess::IOBoundProcess(int id) : Process(id), minBurst(5), maxBurst(15), minIO(50),
					 maxIO(200) {
    lastTime = 0;
    blockedUntil = 0;
    remainingBurst = 0;
}

bool IOBoundProcess::isBlocked(int curCycleNum) const {
    
    return curCycleNum < blockedUntil;
}

int IOBoundProcess::simulate(int curCycleNum, int sliceSize) {
    /* 
     * if the process isn't blocked, the process generates a burst size if needed, then
     * simulates running the process until the end of the burst or the slice, whichever comes
     * first. if the burst finishes, it generates a wait time during which the process is
     * blocked.
     */ 
    // if the process was blocked, and is now unblocked, choose a length for the next CPU burst
    if(curCycleNum >= blockedUntil && remainingBurst == 0) {
	remainingBurst = random()%(maxBurst - minBurst + 1) + minBurst;
    }

    int timeUsed = 0;
    if(remainingBurst > 0) { // if the process is not blocked
	waitTime += curCycleNum - lastTime;

	if(remainingBurst > sliceSize) { // if the whole window will be used...
	    remainingBurst -= sliceSize;
	    timeUsed = sliceSize;

	    // when the process next uses the CPU, it will have been waiting since the end of
	    // this window.
	    lastTime = curCycleNum + sliceSize;
	}
	else { // otherwise the process will block without using the whole window
	    timeUsed = remainingBurst;
	    remainingBurst = 0;

	    // choose a time for the IO request to complete
	    blockedUntil = curCycleNum + timeUsed + random()%(maxIO - minIO + 1) + minIO;
	    // when the process next uses the CPU, it will have been
	    // waiting since it unblocked (not since the end of this window).
	    lastTime = blockedUntil;
	}
    }

    cpuTime += timeUsed;
    return timeUsed;
}
