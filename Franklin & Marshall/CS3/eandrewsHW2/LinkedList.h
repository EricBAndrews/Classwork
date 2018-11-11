#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"List.h"
#include"LinkedListNode.h"
#include<iostream>

template <class item_t>
class LinkedList : public List<item_t> {
protected:
    LinkedListNode<item_t>* head;
    LinkedListNode<item_t>* tail;
    int size;

public:
    LinkedList() {
	head = 0;
	tail = 0;
	size = 0;
    }

    ~LinkedList() {
	LinkedListNode<item_t>* cur = head;
	LinkedListNode<item_t>* next;
	while (cur) {
	    next = cur->getNext();
	    delete cur;
	    cur = next;
	}
    }

    virtual void pushBack(const item_t& item) {
	LinkedListNode<item_t>* toPush = new LinkedListNode<item_t>(0, item);
	if (tail) {
	    tail->setNext(toPush);
	}
	else { // if list is empty, initialize head to new node as well
	    head = toPush;
	}
	tail = toPush;
	++size;
    }
    virtual void popBack() {
	LinkedListNode<item_t>* cur = head;
	if (cur == tail) { // size == 1
	    delete cur;
	    head = 0;
	    tail = 0;
	}
	else {
	    while (cur->getNext() != tail) { // find item preceding tail
		cur = cur->getNext();
	    }
	    delete tail;
	    tail = cur; // set new tail
	    tail->setNext(0); // avoid segfaulting :)
	}
	--size;
    }
    virtual const item_t& getBack() const {
	return tail->getItem();
    }

    virtual void pushFront(const item_t& item) {
	LinkedListNode<item_t>* toPush = new LinkedListNode<item_t>(head, item);
	head = toPush;
	if (!tail) { // if list is empty, initialize tail to new node as well
	    tail = toPush;
	}
	++size;
    }
    virtual void popFront() {
	LinkedListNode<item_t>* temp = head;
	head = head == tail ? 0 : head->getNext();
	delete temp;
	--size;
    }
    virtual const item_t& getFront() const {
	return head->getItem();
    }

    virtual const item_t& getItem(int index) const {
	LinkedListNode<item_t>* ret = head;
	for (int i = 0; i < index; ++i) {
	    ret = ret->getNext();
	}
	return ret->getItem();
    }
    virtual void setItem(int index, const item_t& item) {
	LinkedListNode<item_t>* toSet = head;
	for (int i = 0; i < index; ++i) {
	    toSet = toSet->getNext();
	}
	toSet->setItem(item);
    }

    virtual void insert(int index, const item_t& item) {
	LinkedListNode<item_t>* toInsert = new LinkedListNode<item_t>(0, item);
	LinkedListNode<item_t>* pre = new LinkedListNode<item_t>(head, 0);
	for (int i = 0; i < index; ++i) { // find item before insertion
	    pre = pre->getNext();
	}
	toInsert->setNext(pre->getNext());
	pre->setNext(toInsert);
	if (index == 0) {
	    head = toInsert;
	}
	if (index == size) {
	    tail = toInsert;
	}
	++size;
    }

    virtual void remove(int index) {
	LinkedListNode<item_t>* cur = new LinkedListNode<item_t>(head, 0);
	for (int i = 0; i < index; ++i) {
	    cur = cur->getNext();
	}
	LinkedListNode<item_t>* toRemove = cur->getNext();
	if (index == 0) {
	    head = toRemove->getNext();
	}
	else if (index == size - 1) {
	    tail = cur;
	    tail->setNext(0);
	}
	else {
	    cur->setNext(toRemove->getNext());
	}
	delete toRemove;
	--size;
    }

    virtual int getSize() const {
	return size;
    }

    virtual bool isEmpty() const {
	return (size == 0);
    }

    virtual void printList() {
	// for testing use only
	std::cout << "|";
	LinkedListNode<item_t>* cur = head;
	while (cur) {
	    std::cout << cur->getItem() << "|";
	    cur = cur->getNext();
	}
	std::cout << std::endl;
    }
};

#endif
