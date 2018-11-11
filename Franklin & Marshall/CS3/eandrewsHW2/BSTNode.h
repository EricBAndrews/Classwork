#ifndef BSTNODE_H
#define BSTNODE_H

template<class key_t, class val_t>
class BSTNode {
protected:
  key_t key;
  val_t val;
  BSTNode* parent;
  BSTNode* left;
  BSTNode* right;

public:
  // constructors
  BSTNode();
  
  BSTNode(const key_t& newKey, const val_t& newVal);
  
  virtual ~BSTNode();

  // getters & setters
  const val_t& getValue();
  void setValue(const val_t& newVal);

  const key_t& getKey();
  void setKey(const key_t& newKey);

  virtual BSTNode* getParent() const;
  virtual void setParent(BSTNode* newParent);

  virtual BSTNode* getLeftChild() const;
  virtual void setLeftChild(BSTNode* newLeft);

  virtual BSTNode* getRightChild() const;
  virtual void setRightChild(BSTNode* newRight);
};

///////////////////////////////////////////
// implementation of bstnode begins here //
///////////////////////////////////////////

// public
template<class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode() {
  this->left = 0;
  this->right = 0;
  this->parent = 0;
}

template<class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& newKey, const val_t& newVal) {
  left = 0;
  right = 0;
  key = newKey;
  val = newVal;
}

template<class key_t, class val_t>
BSTNode<key_t, val_t>::~BSTNode() {
}

template<class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() {
  return val;
}

template<class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& newVal) {
  val = newVal;
}

template<class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() {
  return key;
}

template<class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& newKey) {
  key = newKey;
}

template<class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent() const {
  return parent;
}

template<class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode* newParent) {
  parent = newParent;
}

template<class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild() const {
  return left;
}

template<class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode* newLeft) {
  left = newLeft;
}

template<class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild() const {
  return right;
}

template<class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode* newRight) {
  right = newRight;
}

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
