#include"binaryHeap.h"
#include<iostream>

void BinaryHeap::swap(int pos0, int pos1) {
  int temp = items[pos0];;
  items[pos0] = items[pos1];
  items[pos1] = temp;
}

void BinaryHeap::fixDown(int pos) {
  while(pos * 2 <= size) {
    int next = 2 * pos;
    // find smallest next
    if (next + 1 <= size && prios[items[next]] > prios[items[next+1]]) {
      ++next;
    }
    // ensure heap property is still violated
    if (prios[items[pos]] <= prios[items[next]]) {
      break;
    }
    swap(pos, next);
    pos = next;
  }
}

BinaryHeap::BinaryHeap(const double* priorities, int numItems) {
  items = new int[numItems+1];
  prios = new double[numItems+1];
  size = 0;
  while(size < numItems) {
    ++size;
    prios[size] = priorities[size-1];
    items[size] = size;
    int cur = size;
    while (cur > 1) {
      if (prios[items[cur]] >= prios[items[cur/2]]) {
        break;
      }
      swap(cur, cur/2);
    }
  }
}

BinaryHeap::~BinaryHeap() {
  delete[] items;
  delete[] prios;
}

int BinaryHeap::getMin() const {
  return items[1];
}

void BinaryHeap::popMin() {
  items[1] = items[size];
  --size;
  fixDown(1);
}

bool BinaryHeap::contains(int item) const {
  return item > 0 && item < size && prios[item] >= prios[items[1]];
}

double BinaryHeap::getPriority(int item) const {
  return prios[item];
}

void BinaryHeap::decreasePriority(int item, double newPriority) {
  // bad runtime
  int i = getPos(item);
  if (newPriority < prios[item]) {
    prios[item] = newPriority;
  }
  fixDown(i);
}

int BinaryHeap::getSize() const {
  return size;
}

int BinaryHeap::getPos(int item) const {
  // bad runtime
  int i = 1;
  for (; i <= size; ++i) {
    if (items[i] == item) {
      break;
    }
  }
  return i;
}
