#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include "ArrayList.h"

TEST_CASE("TESTING ArrayList class") {

    SECTION("constructors") {
	ArrayList<int>* list0 = new ArrayList<int>();
	ArrayList<int>* list1 = new ArrayList<int>(5);

	CHECK(list0->getSize() == 0);
	CHECK(list1->getSize() == 0);
	CHECK(list0->getCapacity() == 10);
	CHECK(list1->getCapacity() == 5);
	CHECK(list0->isEmpty());
	CHECK(list1->isEmpty());

	delete list0;
	delete list1;
    }

    SECTION("basic operations") {
	ArrayList<int>* list0 = new ArrayList<int>(2);

	list0->pushBack(1);
	list0->pushBack(2);
	list0->pushBack(3);
	CHECK(list0->getBack() == 3);
	list0->popBack();
	CHECK(list0->getSize() == 2);
	CHECK(list0->getCapacity() == 4);
	CHECK(list0->getBack() == 2);
	list0->pushFront(0);
	list0->pushFront(-1);
	list0->pushFront(-2);
	CHECK(list0->getFront() == -2);
	list0->popFront();
	CHECK(list0->getSize() == 4);
	CHECK(list0->getCapacity() == 8);
	CHECK(list0->getFront() == -1);
	list0->insert(3, 25);
	list0->insert(4, 6);
	list0->insert(4, 5);
	list0->insert(4, 4);
	list0->insert(4, 3);
	CHECK(list0->getSize() == 9);
	CHECK(list0->getCapacity() == 16);
	CHECK(list0->getItem(3) == 25);
	CHECK(list0->getItem(5) == 4);
	list0->remove(3);
	list0->setItem(1, 15);
	CHECK(list0->getSize() == 8);
	CHECK(list0->getItem(5) == 5);
	CHECK(list0->getItem(1) == 15);

	delete list0;
    }
}
