#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include"List.h"

template <class item_t>
class ArrayList : public List<item_t> {
protected:
    item_t* items;
    int size;
    int capacity;

public:
    ArrayList() {
	// creates an empty list with capacity 10
	this->items = new item_t[10];
	this->size = 0;
	this->capacity = 10;
    }
    ArrayList(int capacity) {
	// creates a list with the given capacity
	this->items = new item_t[capacity];
	this->size = 0;
	this->capacity = capacity;
    }
    ~ArrayList() {
	delete[] items;
    }

    virtual void pushBack(const item_t& item) {
	// pushes item to the back of the list
	if (this->size == this->capacity) {
	    item_t* temp = new item_t[this->capacity * 2];
	    for (int i = 0; i < this->capacity; ++i) {
		temp[i] = this->items[i];
	    }
	    this->capacity *= 2;
	    delete[] this->items;
	    this->items = temp;
	}
	this->items[this->size] = item;
	++(this->size);
    }	
    virtual void popBack() {
	// removes, but does not return, the last item
	--(this->size);
	this->items[this->size] = 0;
    }
    virtual const item_t& getBack() const {
	// returns a reference to the last item (does not remove it)
	item_t& ret = this->items[size - 1];
	return ret;
    }
    virtual void pushFront(const item_t& item) {
	// pushes item to the front of the list
	if (this->size == this->capacity) {
	    item_t* temp = new item_t[this->capacity * 2];
	    for (int i = 0; i < this->capacity; ++i) {
		temp[i] = this->items[i];
	    }
	    this->capacity *= 2;
	    delete[] this->items;
	    this->items = temp;
	}
	for (int i = size - 1; i > 0; --i) {
	    this->items[i] = this->items[i - 1];
	}
	this->items[0] = item;
	++(this->size);
    }
    virtual void popFront() {
	// removes, but does not return, the first item
	--(this->size);
	for (int i = 0; i < size; ++i) {
	    this->items[i] = this->items[i + 1];
	}
    }
    const item_t& getFront() const {
	// returns a reference to the first item (does not remove it)
	item_t& ret = this->items[0];
	return ret;
    }

    virtual const item_t& getItem(int index) const {
	// returns a reference to the item at the given index
	item_t& ret = this->items[index];
	return ret;
    }
    virtual void setItem(int index, const item_t& item) {
	// sets the item at the given index
	this->items[index] = item;
    }

    virtual void insert(int index, const item_t& item) {
	// inserts the given item at the given index (items at index or beyond shift up one
	// position) inserting just past the last element (i.e. position size) shoud be
	// equivalent to pushBack.
	if (this->size == this->capacity) {
	    item_t* temp = new item_t[this->capacity * 2];
	    for (int i = 0; i < this->capacity; ++i) {
		temp[i] = this->items[i];
	    }
	    this->capacity *= 2;
	    delete[] this->items;
	    this->items = temp;
	}
	for (int i = this->size; i > index; --i) {
	    this->items[i] = this->items[i - 1];
	}
	this->items[index] = item;
	++(this->size);
    }
    virtual void remove(int index) {
	// removes the item at the given index (items beyond index shift down one position)
	for (int i = index; i < size; i ++) {
	    this->items[i] = this->items[i + 1];
	}
	--(this->size);
    }

    virtual int getSize() const {
	// returns the number of items in the list
	return this->size;
    }
	
    virtual bool isEmpty() const {
	// returns true if the list is empty (false otherwise)
	return (this->items[0]) ? false : true;
    }
    
    virtual int getCapacity() const {
	// returns the size of the array that contains the list
	return this->capacity;
    }
};

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
