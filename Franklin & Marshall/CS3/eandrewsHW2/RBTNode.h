#ifndef RBT_NODE
#define RBT_NODE

#include "BSTNode.h"

template <class key_t, class val_t>
class RBTNode : public BSTNode<key_t, val_t>
{
  protected:
   // 0 = black, 1 = red
   bool color;

  public:
   //Children, parent initialized to zero
   RBTNode(const key_t& key, const val_t& value, bool color);

   RBTNode<key_t, val_t>* getParent() const;
   RBTNode<key_t, val_t>* getLeftChild() const;
   RBTNode<key_t, val_t>* getRightChild() const;

   virtual void setColor(bool newColor);
   virtual bool getColor() const;
};

/////////////////////////////////////////
//Implementation of RBTNode begins here//
/////////////////////////////////////////

///YOUR JOB: Implement the constructor right here
template <class key_t, class val_t>
RBTNode<key_t, val_t>::RBTNode(const key_t& key, const val_t& value, bool color) {
  this->setKey(key);
  this->setValue(value);
  this->color = color;
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getParent() const {
   return dynamic_cast<RBTNode<key_t, val_t>* >(BSTNode<key_t, val_t>::getParent());
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getLeftChild() const {
   return dynamic_cast<RBTNode<key_t, val_t>* >(BSTNode<key_t, val_t>::getLeftChild());
}

template <class key_t, class val_t>
RBTNode<key_t, val_t>* RBTNode<key_t, val_t>::getRightChild() const {
   return dynamic_cast<RBTNode<key_t, val_t>* >(BSTNode<key_t, val_t>::getRightChild());
}

template <class key_t, class val_t>
bool RBTNode<key_t, val_t>::getColor() const {
   return color;
}

template <class key_t, class val_t>
void RBTNode<key_t, val_t>::setColor(bool newColor) {
   color = newColor;
}

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
