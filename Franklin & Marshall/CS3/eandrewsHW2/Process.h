#ifndef PROCESS
#define PROCESS

// an abstract class representing a process
class Process {
protected:
    const int id;
    int cpuTime;
    int waitTime;

    int lastTime; // the time the process last started waiting for the CPU

public:
    Process(int id);

    virtual ~Process() { } // an empty virtual destructor for the sake of inheritance
   
    virtual int getID() const; // returns the process' ID number
    virtual int getCPUTime() const; // returns the total CPU time the process has used
    // returns the total amount of time the process was ready to run (not blocked), but not
    // running. curCycleNum is the number of simulated cycles so far.
    virtual int getWaitTime(int curCycleNum) const;
   
    // returns true if the process is blocked
    virtual bool isBlocked(int curCycleNum) const = 0;

    // simulates giving the process sliceSize time on the CPU. curCycleNum is the number of
    // simulated cycles so far (used to calculate wait time etc.) returns the number of CPU
    // cycles the process actually consumes.
    virtual int simulate(int curCycleNum, int sliceSize) = 0;
};

// a concrete class representing a CPU-bound process (a process that uses all CPU time given to
// it)
class CPUBoundProcess : public Process {
public:
    CPUBoundProcess(int id);
   
    virtual bool isBlocked(int curCycleNum) const; // returns false...the process is never blocked

    virtual int simulate(int curCycleNum, int sliceSize); // returns sliceSize... the process
    // uses all the CPU time
};

// a concrete class representing an I/O-bound process a process that frequently blocks to wait
// for I/O)
class IOBoundProcess : public Process {
protected:
    // the min/max CPU burst times
    const int minBurst;
    const int maxBurst;

    // the min/max I/O request times
    const int minIO;
    const int maxIO;

    // the time when the process will unblock
    int blockedUntil;
    // the amount of time remaining in the current CPU burst
    int remainingBurst;

public:
    IOBoundProcess(int id);
    // the process may be blocked!
    virtual bool isBlocked(int curCycleNum) const;
    // the process may use less time than sliceSize (if it blocks in the middle of the slice)
    virtual int simulate(int curCycleNum, int sliceSize);
};

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
