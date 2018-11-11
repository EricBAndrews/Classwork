#include "Scheduler.h"
#include "Process.h"

#include <iostream>
#include <chrono>

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles) {
  // creates cpu-bound processes
  ArrayList<Process*> cpuProcs;
  for(int i = 0; i < numCPUBound; i++) {
    cpuProcs.pushBack(new CPUBoundProcess(i));
    sched->addProcess(cpuProcs.getBack());
  }

  // creates io-bound processes
  ArrayList<Process*> ioProcs;
  for(int i = 0; i < numIOBound; i++) {
    ioProcs.pushBack(new IOBoundProcess(i+numCPUBound));
    sched->addProcess(ioProcs.getBack());
  }

  auto start = chrono::system_clock::now(); // gets start time
  // initialize simulated cpu
  int numSchedules = 0;
  int curCycle = 0;

  // runs simulation for given number of cycles
  while(curCycle < numCycles) {
    // std::cout << "cycle " << curCycle << std::endl;
    Process* p = sched->popNext(curCycle); // get first non-blocked schedule
    numSchedules++; // count total schedules
    // simulate running schedule for a slice of 10 cycles
    if(p != 0) { 
      curCycle += p->simulate(curCycle, 10);
      sched->addProcess(p);
    }
    // null pointer handling
    else {
      curCycle += 10;
    }
  }

  // get elapsed time
  auto end = chrono::system_clock::now();
  auto dur = end - start;
  auto durNS = chrono::duration_cast<chrono::nanoseconds>(dur);

  // calculate total cpu and wait time for cpu-bound functions
  double cpuCPUTime = 0;
  double cpuWaitTime = 0;
  for(int i = 0; i < cpuProcs.getSize(); i++) { // for each process
    // add process cpu, wait time to total
    Process* p = cpuProcs.getItem(i); 
    cpuCPUTime += p->getCPUTime();
    cpuWaitTime += p->getWaitTime(curCycle);
    delete p; // delete now unnecessary process
  }

  // calculate total cpu and wait time for io-bound functions
  double ioCPUTime = 0;
  double ioWaitTime = 0;
  for(int i = 0; i < ioProcs.getSize(); i++) { // for each process
    // add process cpu, wait time to total
    Process* p = ioProcs.getItem(i);
    ioCPUTime += p->getCPUTime();
    ioWaitTime += p->getWaitTime(curCycle);
    delete p;
  }

  double* results = new double[5]; // return array
  // calculate nanoseconds per scheduler call & averages of cpu and wait time, add them to the
  // return array
  results[0] = double(durNS.count())/numSchedules;
  results[1] = cpuCPUTime/numCPUBound;
  results[2] = cpuWaitTime/numCPUBound;
  results[3] = ioCPUTime/numIOBound;
  results[4] = ioWaitTime/numIOBound;
  return results;
}


