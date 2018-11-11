#ifndef BST_FORWARD_ITERATOR
#define BST_FORWARD_ITERATOR

#include "BSTNode.h"

template <class key_t, class val_t>
class BSTForwardIterator {
protected:
  BSTNode<key_t, val_t>* current; // the node the iterator currently points to
  BSTNode<key_t, val_t>* sentinel; // the value representing the non-node
   
public:
  BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel);

  virtual void next();

  virtual bool isPastEnd() const;

  virtual const key_t& getKey() const;

  virtual const val_t& getValue() const;
   
  virtual void setValue(const val_t& newVal);
  
  virtual void print();
  
  template <class k_t, class v_t> friend class BSTMultimap; // allow access to private members
  template <class k_t, class v_t> friend class RBTMultimap;
};

////////////////////////////////////////////////////
//Implementation of BSTForwardIterator begins here//
////////////////////////////////////////////////////

// public
template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node,
                                                     BSTNode<key_t, val_t>* sentinel) {
  this->sentinel = sentinel;
  current = node;
}

template<class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::next() {
  // points the iterator at the successor of its current node
  if (current != sentinel) {
    if (current->getRightChild() != sentinel) {
      // if right subtree exists, find its smallest node
      current = current->getRightChild();
      while (current->getLeftChild() != sentinel) {
        current = current->getLeftChild();
      }
    }
    else {
      BSTNode<key_t, val_t>* parent = current->getParent();
      while(parent != sentinel && current == parent->getRightChild()) {
        current = parent;
        parent = parent->getParent();
      }
      current = parent;
    }
  }
}

template<class key_t, class val_t>
bool BSTForwardIterator<key_t, val_t>::isPastEnd() const {
  return current == sentinel;
}

template<class key_t, class val_t>
const key_t& BSTForwardIterator<key_t, val_t>::getKey() const {  
  return current->getKey();
}

template<class key_t, class val_t>
const val_t& BSTForwardIterator<key_t, val_t>::getValue() const {
  return current->getValue();
}

template<class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::setValue(const val_t& newVal) {
  current->setValue(newVal);
}

template<class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::print() {
  // testing purposes only
  std::cout << "key: " << current->getKey()
            << " value: " << current->getValue() << std::endl;
}

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
