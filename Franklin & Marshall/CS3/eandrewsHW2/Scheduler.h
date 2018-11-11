#ifndef SCHEDULER_H
#define SCHEDULER_H

#include"Process.h"
#include"List.h"
#include"ArrayList.h"
#include"LinkedList.h"
#include"BSTMultimap.h"
#include"RBTMultimap.h"

class Scheduler {
public:
  virtual void addProcess(Process* proc) = 0;
  virtual Process* popNext(int curCycle) = 0;
  virtual ~Scheduler() {}
};

class RoundRobin : public Scheduler {
protected:
  List<Process*>* procQueue;

public:
  RoundRobin();
  ~RoundRobin();
    
  virtual void addProcess(Process* proc);
  virtual Process* popNext(int curCycle);
};

class FastRoundRobin : public RoundRobin {
public:
  FastRoundRobin();
};

class CompletelyFair : public Scheduler {
protected:
  BSTMultimap<int, Process*>* procTree;

public:
  CompletelyFair();
  ~CompletelyFair();
  virtual void addProcess(Process* proc);
  virtual Process* popNext(int curCycle);
};

class FastCompletelyFair : public CompletelyFair {
public:
  FastCompletelyFair();
};

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
