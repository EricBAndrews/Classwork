#include"Scheduler.h"

// RoundRobin
RoundRobin::RoundRobin() {
  this->procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin() {
  delete this->procQueue;
}

void RoundRobin::addProcess(Process* proc) {
  procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle) {
  Process* ret;
  for (int i = 0; i < procQueue->getSize(); ++i) {
    ret = procQueue->getFront();
    procQueue->popFront();
    if (ret->isBlocked(curCycle)) {
      procQueue->pushBack(ret);
    }
    else {
      return ret;
    }
  }
  return 0;
}

// FastRoundRobin
FastRoundRobin::FastRoundRobin() {
  delete this->procQueue;
  this->procQueue = new LinkedList<Process*>();
}

// CompletelyFair
CompletelyFair::CompletelyFair() {
  procTree = new BSTMultimap<int, Process*>();
}

CompletelyFair::~CompletelyFair() {
  this->procTree->clear();
  delete this->procTree;
}

void CompletelyFair::addProcess(Process* proc) {
  procTree->insert(proc->getCPUTime(), proc);
}

Process* CompletelyFair::popNext(int curCycle) {
  BSTForwardIterator<int, Process*> iterator = procTree->getMin();
  while (!iterator.isPastEnd() && iterator.getValue()->isBlocked(curCycle)) {
    iterator.next();
  }
  if (iterator.isPastEnd()) {
    return 0;
  }
  Process* ret = iterator.getValue();
  iterator = procTree->remove(iterator);
  return ret;
}

// FastCompletelyFair
FastCompletelyFair::FastCompletelyFair() {
  delete this->procTree;
  this->procTree = new RBTMultimap<int, Process*>();
};
