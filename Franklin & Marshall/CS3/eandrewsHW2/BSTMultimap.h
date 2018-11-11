#ifndef BSTMULTIMAP_H
#define BSTMULTIMAP_H

#include"BSTForwardIterator.h"
#include<queue>

template<class key_t, class val_t>
class BSTMultimap {
protected:
  // members
  BSTNode<key_t, val_t>* root;
  BSTNode<key_t, val_t>* sentinel;
  int numItems;

  // helper functions
  virtual void printTreeHelper(BSTNode<key_t, val_t>* root, int depth);

  virtual void insertNode(BSTNode<key_t, val_t>* newNode);

  virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace,
                          BSTNode<key_t, val_t>* replacementNode);

public:
  BSTMultimap();

  virtual ~BSTMultimap();

  virtual void insert(const key_t& key, const val_t& val);
  
  virtual int getSize();

  virtual bool isEmpty();

  virtual bool contains(const key_t& key) const;
  
  virtual void clear();

  virtual BSTForwardIterator<key_t, val_t> getMin() const;

  virtual BSTForwardIterator<key_t, val_t> getMax() const;

  virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;

  virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;
  
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);      
  virtual void printTree();
};

/////////////////////////////////////////////
//implementation of bstmultimap begins here//
/////////////////////////////////////////////

// protected
template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTreeHelper(BSTNode<key_t, val_t>* root, int depth) {
  // recursive because i'm lazy
  // it could print a nicer looking answer, but it works
  std::string indent = "  |- ";
  std::string space = "  |  ";
  for (int i = 0; i < depth - 1; ++i) {
    std::cout << space;
  }
  if (depth) {
    std::cout << indent;
  }
  std::cout << "[ " << root->getKey() << " | " << root->getValue() << " ]" << std::endl;
  // std::cout << root->getKey() << " | " << root->getValue() << std::endl;
  if (root->getLeftChild() != sentinel) {
    printTreeHelper(root->getLeftChild(), depth + 1);
  }
  if (root->getRightChild() != sentinel) {
    printTreeHelper(root->getRightChild(), depth + 1);
  }
}

template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode) {
  BSTNode<key_t, val_t>* prev = sentinel;
  BSTNode<key_t, val_t>* walker = root;
  while (walker != sentinel) {
    prev = walker;
    if (newNode->getKey() < walker->getKey()) {
      walker = walker->getLeftChild();
    }
    else {
      walker = walker->getRightChild();
    }
  }
  newNode->setParent(prev);
  if (prev == sentinel) {
    root = newNode;
  }
  else if (newNode->getKey() < prev->getKey()) {
    prev->setLeftChild(newNode);
  }
  else {
    prev->setRightChild(newNode);
  }
  ++numItems;
}

template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace,
                                           BSTNode<key_t, val_t>* replacementNode) {
  
  BSTNode<key_t, val_t>* parent = nodeToReplace->getParent();
  if (replacementNode != sentinel) {
    replacementNode->setParent(parent);
  }
  if (parent == this->sentinel) {
    this->root = replacementNode;
  }
  else if (nodeToReplace == parent->getLeftChild()) {
    parent->setLeftChild(replacementNode);
  }
  else {
    parent->setRightChild(replacementNode);
  }
}

// public
template<class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap() {
  //sentinel = new BSTNode<key_t, val_t>();
  sentinel = 0;
  root = sentinel;
  numItems = 0;
}

template<class key_t, class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap() {
  clear();
}

template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val) {
  BSTNode<key_t, val_t>* toInsert = new BSTNode<key_t, val_t>(key, val);
  toInsert->setLeftChild(sentinel);
  toInsert->setRightChild(sentinel);
  insertNode(toInsert);
  return;
}

template<class key_t, class val_t>
int BSTMultimap<key_t, val_t>::getSize() {
  return numItems;
}

template<class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty() {
  return !numItems;
}

template<class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const {
  BSTNode<key_t, val_t>* walker = root;
  while (walker != sentinel) {
    if (key == walker->getKey()) {
      return true;
    }
    if (key < walker->getKey()) {
      walker = walker->getLeftChild();
    }
    else {
      walker = walker->getRightChild();
    }
  }
  return false;
}

template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear() {
  numItems = 0;
  if (root == sentinel) {
    return;
  }
  std::queue<BSTNode<key_t, val_t>*> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    BSTNode<key_t, val_t>* cur = nodes.front();
    nodes.pop();
    if (cur->getLeftChild() != sentinel) {
      nodes.push(cur->getLeftChild());
    }
    if (cur->getRightChild() != sentinel) {
      nodes.push(cur->getRightChild());
    }
    delete cur; // delete throws an error
  }
  root = sentinel;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const {
  BSTNode<key_t, val_t>* min = root;
  while (min->getLeftChild() != sentinel) {
    min = min->getLeftChild();
  }
  BSTForwardIterator<key_t, val_t> ret = BSTForwardIterator<key_t, val_t>(min, sentinel);
  return ret;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const {
  BSTNode<key_t, val_t>* max = root;
  while (max->getRightChild() != sentinel) {
    max = max->getRightChild();
  }
  BSTForwardIterator<key_t, val_t> ret = BSTForwardIterator<key_t, val_t>(max, sentinel);
  return ret;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const {
  BSTForwardIterator<key_t, val_t> ret = this->getMin();
  while (ret.getKey() != key) {
    ret.next();
  }
  if (ret.isPastEnd()) {
    return BSTForwardIterator<key_t, val_t>(this->sentinel, this->sentinel);
  }
  return ret;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findLast (const key_t& key) const {
  BSTForwardIterator<key_t, val_t> temp = this->getMin();
  BSTForwardIterator<key_t, val_t> ret(this->sentinel, this->sentinel);
  while (!temp.isPastEnd() && temp.getKey() <= key) {
    if (temp.getKey() == key) {
      ret = temp;
    }
    temp.next();
  }
  return ret;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(
  const BSTForwardIterator<key_t, val_t>& pos) {
  // cormen algorithm
  BSTNode<key_t, val_t>* toRemove = pos.current;
  BSTForwardIterator<key_t, val_t> successor = pos;
  successor.next();
  if (toRemove->getLeftChild() == sentinel) {
    if (toRemove->getRightChild() != sentinel) {
      // right child etc. exists
      transplant(toRemove, successor.current);
    }
    else {
      // no children
      if (toRemove == toRemove->getParent()->getLeftChild()) {
        toRemove->getParent()->setLeftChild(sentinel);
      }
      else {
        toRemove->getParent()->setRightChild(sentinel);
      }
    }
  }
  else if (toRemove->getRightChild() == sentinel) {
    transplant(toRemove, toRemove->getLeftChild());
  }
  else {
    BSTNode<key_t, val_t>* replacement = successor.current;
    if (replacement->getParent() != toRemove) {
      transplant(replacement, replacement->getRightChild());
      replacement->setRightChild(toRemove->getRightChild());
      replacement->getRightChild()->setParent(replacement);
    }
    transplant(toRemove, replacement);
    replacement->setLeftChild(toRemove->getLeftChild());
    replacement->getRightChild()->setParent(replacement);
  }
  --numItems;
  return successor;
}

template<class key_t, class val_t>
void BSTMultimap<key_t, val_t>::printTree() {
  // testing purposes only
  printTreeHelper(root, 0);
}

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
