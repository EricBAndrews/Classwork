#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include "LinkedList.h"

TEST_CASE("TESTING LinkedList class") {

    SECTION("constructors") {
	LinkedList<int>* list0 = new LinkedList<int>();

	CHECK(list0->getSize() == 0);
	CHECK(list0->isEmpty());

	delete list0;
    }

    SECTION("basic operations") {
    	LinkedList<int>* list0 = new LinkedList<int>();
	LinkedList<int>* list1 = new LinkedList<int>();

	// push, pop
	list0->pushBack(1);
	list0->popBack();
	list0->pushBack(1);
	list0->popFront();
	list0->pushFront(1);
	list0->pushBack(2);
	list0->pushBack(3);
	list0->pushFront(0);
	list0->pushFront(-1);
	list0->popBack();
	list0->popFront();
	CHECK(list0->getSize() == 3);

	// get
	CHECK(list0->getFront() == 0);
	CHECK(list0->getItem(1) == 1);
	CHECK(list0->getBack() == 2);

	// insert, remove
	list0->insert(0, 100);
	list0->insert(2, 5);
	list0->insert(4, 15);
	list0->insert(6, 25);
	CHECK(list0->getSize() == 7);
	CHECK(list0->getItem(0) == 100);
	CHECK(list0->getItem(2) == 5);
	CHECK(list0->getItem(4) == 15);
	CHECK(list0->getItem(6) == 25);
	list0->remove(6);
	list0->remove(4);
	list0->remove(2);
	list0->remove(0);
	CHECK(list0->getSize() == 3);
	CHECK(list0->getFront() == 0);
	CHECK(list0->getItem(1) == 1);
	CHECK(list0->getBack() == 2);

	// fringe cases
	list1->pushFront(0);
	list1->remove(0);
	list1->pushFront(0);
	CHECK(list1->getFront() == 0);
	CHECK(list1->getBack() == 0);
	list1->setItem(0, 8);
	CHECK(list1->getItem(0) == 8);
	list1->pushBack(15);
	list1->setItem(1, 16);
	CHECK(list1->getBack() == 16);
	CHECK(list1->getItem(1) == 16);

    	delete list0;
	delete list1;
    }
}
