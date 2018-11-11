#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
protected:
  // performs the rotate left operation (assumes node has a right child)
  virtual void rotateLeft(BSTNode<key_t, val_t>* node);

  // performs the rotate right operation (assumes node has a left child)
  virtual void rotateRight(BSTNode<key_t, val_t>* node);

  // fix up the tree after an insert (assumes insertedNode is red)
  virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

  // fix up the tree after deleting a node
  // replacementNode is the node that replaced the deleted node (possibly the sentinel)
  virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

  // puts replacementNode in nodeToReplace's position in the tree (replacementNode takes its
  // children along with it)
  // assumes nodeToReplace is a real node (not the sentinel)
  virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace,
                          BSTNode<key_t, val_t>* replacementNode);

public:
  //Creates an empty red-black tree
  RBTMultimap();
  virtual ~RBTMultimap();

  // inserts (key, value) into the multimap
  virtual void insert(const key_t& key, const val_t& value);

  // removes the key/value pair pointed to by pos (if pos is off the end, does nothing)
  // returns an iterator pointing to the next node after the deleted node
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

  // prints the tree in the "dot" format for visualization using graphviz
  // NOTE: Requires that keys are streamable (values are not printed)
  virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

// protected
template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node) {
  BSTNode<key_t, val_t>* right = node->getRightChild();
  node->setRightChild(right->getLeftChild());
  if (right->getLeftChild() != this->sentinel) {
    right->getLeftChild()->setParent(node);
  }
  BSTNode<key_t, val_t>* parent = node->getParent();
  right->setParent(parent);
  if (parent == this->sentinel) {
    this->root = right;
  }
  else if (node == parent->getLeftChild()) {
    parent->setLeftChild(right);
  }
  else {
    parent->setRightChild(right);
  }

  right->setLeftChild(node);
  if (node->getLeftChild() != this->sentinel) {
    node->getLeftChild()->setParent(node);
  }
  right->setParent(parent);
  node->setParent(right);
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node) {
  BSTNode<key_t, val_t>* left = node->getLeftChild();
  node->setLeftChild(left->getRightChild());
  if (left->getRightChild() != this->sentinel) {
    left->getRightChild()->setParent(node);
  }
  BSTNode<key_t, val_t>* parent = node->getParent();
  left->setParent(parent);
  if (parent == this->sentinel) {
    this->root = left;
  }
  else if (node == parent->getRightChild()) {
    parent->setRightChild(left);
  }
  else {
    parent->setLeftChild(left);
  }
  
  left->setRightChild(node);
  if (node->getRightChild() != this->sentinel) {
    node->getRightChild()->setParent(node);
  }
  left->setParent(parent);
  node->setParent(left);
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode) { // z
  // cormen's algorithm with some variables added to prevent calls (saves ~200ns per call!)
  RBTNode<key_t, val_t>* uncle; // y
  RBTNode<key_t, val_t>* parent;
  RBTNode<key_t, val_t>* grandparent;
  while (insertedNode->getParent()->getColor()) {
    parent = insertedNode->getParent();
    grandparent = parent->getParent();
    if (parent == grandparent->getLeftChild()) {
      uncle = grandparent->getRightChild();
      if (uncle->getColor()) {
        parent->setColor(false);
        uncle->setColor(false);
        grandparent->setColor(true);
        insertedNode = grandparent;
      }
      else {
        if (insertedNode == parent->getRightChild()) {
          insertedNode = parent;
          rotateLeft(insertedNode);
        }
        insertedNode->getParent()->setColor(false);
        insertedNode->getParent()->getParent()->setColor(true);
        rotateRight(insertedNode->getParent()->getParent());
      }
    }
    else {
      uncle = grandparent->getLeftChild();
      if (uncle->getColor()) {
        parent->setColor(false);
        uncle->setColor(false);
        grandparent->setColor(true);
        insertedNode = grandparent;
      }
      else {
        if (insertedNode == parent->getLeftChild()) {
          insertedNode = parent;
          rotateRight(insertedNode);
        }
        insertedNode->getParent()->setColor(false);
        insertedNode->getParent()->getParent()->setColor(true);
        rotateLeft(insertedNode->getParent()->getParent());
      }
    }
  }
  dynamic_cast<RBTNode<key_t, val_t>*>(this->root)->setColor(false);
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode) { // x
  RBTNode<key_t, val_t>* sibling; // w
  RBTNode<key_t, val_t>* parent;
  while (replacementNode != this->root && !replacementNode->getColor()) {
    parent = replacementNode->getParent();
    if (replacementNode == parent->getLeftChild()) {
      sibling = parent->getRightChild();
      if (sibling->getColor()) {
        sibling->setColor(false);
        parent->setColor(true);
        rotateLeft(parent);
        sibling = parent->getRightChild();
      }
      if (!sibling->getLeftChild()->getColor() && !sibling->getRightChild()->getColor()) {
        sibling->setColor(true);
        replacementNode = parent;
      }
      else {
        if (!sibling->getRightChild()->getColor()) {
          sibling->getLeftChild()->setColor(false);
          sibling->setColor(true);
          rotateRight(sibling);
          sibling = parent->getRightChild();
        }
        sibling->setColor(parent->getColor());
        parent->setColor(false);
        sibling->getRightChild()->setColor(false);
        rotateLeft(parent);
        replacementNode = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
      }
    }
    else {
      sibling = parent->getLeftChild();
      if (sibling->getColor()) {
        sibling->setColor(false);
        parent->setColor(true);
        rotateRight(parent);
        sibling = parent->getLeftChild();
      }
      if (!sibling->getRightChild()->getColor() && !sibling->getLeftChild()->getColor()) {
        sibling->setColor(true);
        replacementNode = parent;
      }
      else {
        if (!sibling->getLeftChild()->getColor()) {
          sibling->getRightChild()->setColor(false);
          sibling->setColor(true);
          rotateLeft(sibling);
          sibling = parent->getLeftChild();
        }
        sibling->setColor(parent->getColor());
        parent->setColor(false);
        sibling->getLeftChild()->setColor(false);
        rotateRight(parent);
        replacementNode = dynamic_cast<RBTNode<key_t, val_t>*>(this->root);
      }
    }
  }
  replacementNode->setColor(false);
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace,
                                           BSTNode<key_t, val_t>* replacementNode) {
  BSTNode<key_t, val_t>* parent = nodeToReplace->getParent();
  replacementNode->setParent(parent);
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
RBTMultimap<key_t, val_t>::RBTMultimap() {
  this->sentinel = new RBTNode<key_t, val_t>(key_t(), val_t(), false);
  this->root = this->sentinel;
}

template<class key_t, class val_t>
RBTMultimap<key_t, val_t>::~RBTMultimap() {
  this->clear();
  delete this->sentinel;
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value) {
  RBTNode<key_t, val_t>* toInsert = new RBTNode<key_t, val_t>(key, value, true);
  toInsert->setLeftChild(this->sentinel);
  toInsert->setRightChild(this->sentinel);
  this->insertNode(toInsert);
  this->insertFixup(toInsert);
  return;
}

template<class key_t, class val_t>
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(
  const BSTForwardIterator<key_t, val_t>& pos) {
  RBTNode<key_t, val_t>* toRemove = dynamic_cast<RBTNode<key_t, val_t>*>(pos.current); // z
  RBTNode<key_t, val_t>* replacement = toRemove; // y
  RBTNode<key_t, val_t>* successor; // x
  BSTForwardIterator<key_t, val_t> ret = pos;
  bool replacementColor = replacement->getColor();
  if (toRemove->getLeftChild() == this->sentinel) {
    successor = toRemove->getRightChild();
    transplant(toRemove, toRemove->getRightChild());
  }
  else if (toRemove->getRightChild() == this->sentinel) {
    successor = toRemove->getLeftChild();
    transplant(toRemove, toRemove->getLeftChild());
  }
  else {
    BSTForwardIterator<key_t, val_t> tempPos = pos;
    tempPos.next();
    replacement = dynamic_cast<RBTNode<key_t, val_t>*>(tempPos.current);
    replacementColor = replacement->getColor();
    successor = replacement->getRightChild();
    if (replacement->getParent() == toRemove) {
      successor->setParent(replacement);
    }
    else {
      successor->setParent(replacement->getParent());
      transplant(replacement, replacement->getRightChild());
      replacement->setRightChild(toRemove->getRightChild());
      replacement->getRightChild()->setParent(replacement);
    }
    transplant(toRemove, replacement);
    replacement->setLeftChild(toRemove->getLeftChild());
    replacement->getLeftChild()->setParent(replacement);
    replacement->setColor(toRemove->getColor());
  }
  if (!replacementColor) {
    deleteFixup(successor);
  }
  --this->numItems;
  ret.next();
  return ret;
}

template<class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename) {
  using namespace std;
  ofstream fout(filename.c_str());

  long long counter = 1;
  map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
  nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
  counter++;

  fout << "digraph RBTMultimap {" << endl;

  fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)]
       << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

  if(this->root != this->sentinel)
  {
    RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
    if(!nodeToCounter[rt])
    {
      nodeToCounter[rt] = counter;
      counter++;
    }
    if(!nodeToCounter[rt->getParent()])
    {
      nodeToCounter[rt->getParent()] = counter;
      counter++;
    }
    fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()]
         << " [constraint=false, tailport=n, headport=s";
    if(rt->getParent() == this->sentinel)
    {
      fout << ", color=grey];" << endl;
    }
    else
    {
      //The root's parent is something weird!! Make the arrow orange so it sticks out
      fout << ", color=orange];" << endl;
    }

    map<RBTNode<key_t, val_t>*, bool> printed;
   
    queue<RBTNode<key_t, val_t>* > q;
    q.push(rt);
    while(!q.empty())
    {
      RBTNode<key_t, val_t>* node = q.front();
      q.pop();

      printed[node] = true;
      
      //Set up node's appearance
      if(!nodeToCounter[node])
      {
        nodeToCounter[node] = counter;
        counter++;
      }
      fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() <<
        " | v: " << node->getValue() <<"\", style=filled, color=";
      if(node->getColor())
      {
        fout << "red";
      }
      else
      {
        fout << "black, fontcolor=white";
      }
      fout << "];" << endl;

      //Set up child links
      //First the left node
      if(!nodeToCounter[node->getLeftChild()])
      {
        nodeToCounter[node->getLeftChild()] = counter;
        counter++;
      }
      fout << "\t node" << nodeToCounter[node] << " -> node"
           << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
      if(node->getLeftChild() == this->sentinel)
      {
        fout << ", color=grey";
      }
      else if(printed[node->getLeftChild()])
      {
        fout << ", color=orange";
      }
      else
      {
        q.push(node->getLeftChild());
      }

      if(node->getLeftChild() != this->sentinel)
      {
        if(node->getLeftChild()->getParent() == node)
        {
          //The child's parent pointer points right back,
          //so draw the second arrow
          fout << ", dir=both];" << endl;
        }
        else
        {
          //The child node's parent pointer is not correct!
          //Draw it in orange so it sticks out
          fout << "];" << endl;
          if(!nodeToCounter[node->getLeftChild()->getParent()])
          {
            nodeToCounter[node->getLeftChild()->getParent()] = counter;
            counter++;
          }
          fout << "\t node" << nodeToCounter[node->getLeftChild()]
               << " -> node" << nodeToCounter[node->getLeftChild()->getParent()]
               << " [tailport=n, color=orange];" << endl;
        }
      }
      else
      {
        fout << "];" << endl;
      }

      //Now the right node
      if(!nodeToCounter[node->getRightChild()])
      {
        nodeToCounter[node->getRightChild()] = counter;
        counter++;
      }
      fout << "\t node" << nodeToCounter[node] << " -> node"
           << nodeToCounter[node->getRightChild()] << " [tailport=se";    
      if(node->getRightChild() == this->sentinel)
      {
        fout << ", color=grey";
      }
      else if(printed[node->getRightChild()])
      {
        fout << ", color=orange";
      }
      else
      {
        q.push(node->getRightChild());
      }

      if(node->getRightChild() != this->sentinel)
      {
        if(node->getRightChild()->getParent() == node)
        {
          //The child's parent pointer points right back,
          //so draw the second arrow
          fout << ", dir=both];" << endl;
        }
        else
        {
          //The child node's parent pointer is not correct!
          //Draw it in orange so it sticks out
          fout << "];" << endl;
          if(!nodeToCounter[node->getRightChild()->getParent()])
          {
            nodeToCounter[node->getRightChild()->getParent()] = counter;
            counter++;
          }
          fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node"
               << nodeToCounter[node->getRightChild()->getParent()]
               << " [tailport=n, color=orange];" << endl;
        }
      }
      else
      {
        fout << "];" << endl;
      }
    }
  }
  fout << "}" << endl;
}


// emacs stuff
// Local Variables:
// mode: c++
// End:

#endif
