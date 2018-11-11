#ifndef BINARYHEAP_H
#define BINARYHEAP_H

class BinaryHeap {
private:
  double* prios;
  int* items;
  int size;

  void swap(int item0, int item1);

  void fixDown(int pos);
public:
  // constructors/destructors
  BinaryHeap(const double* priorities, int numItems);

  ~BinaryHeap();

  // heap operations
  int getMin() const;
  
  void popMin();

  bool contains(int item) const;

  double getPriority(int item) const;

  void decreasePriority(int item, double newPriority);

  int getSize() const;

  int getItem(int pos) const;

  int getPos(int item) const;
};
#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
