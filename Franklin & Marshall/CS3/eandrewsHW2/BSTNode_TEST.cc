#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include<string>

#include"BSTNode.h"

TEST_CASE("TESTING BSTNode class") {

    SECTION("constructors") {
	BSTNode<int, std::string>* node0 = new BSTNode<int, std::string>();
	BSTNode<int, std::string>* node1 = new BSTNode<int, std::string>(1, "one");

	CHECK(node0 != 0);
	CHECK(node1 != 0);

	delete node0;
	delete node1;
    }

    SECTION("getters & setters") {
	BSTNode<int, std::string>* node0 = new BSTNode<int, std::string>();
	BSTNode<int, std::string>* node1 = new BSTNode<int, std::string>(1, "one");
	BSTNode<int, std::string>* node2 = new BSTNode<int, std::string>();
	BSTNode<int, std::string>* node3 = new BSTNode<int, std::string>();
	BSTNode<int, std::string>* node4 = new BSTNode<int, std::string>();
	
	node0->setLeftChild(node2);
	node0->setRightChild(node3);
	node0->setParent(node4);
	node1->setLeftChild(node2);
	node1->setRightChild(node3);
	node1->setParent(node4);

	CHECK(node0->getLeftChild() == node2);
	CHECK(node0->getRightChild() == node3);
	CHECK(node0->getParent() == node4);
	CHECK(node1->getLeftChild() == node2);
	CHECK(node1->getRightChild() == node3);
	CHECK(node1->getParent() == node4);
	CHECK(node0->getKey() == 0);
	CHECK(node0->getValue() == "");
	CHECK(node1->getKey() == 1);
	CHECK_FALSE(node1->getValue().compare("one"));
	node0->setKey(2);
	node0->setValue("two");
	CHECK(node0->getKey() == 2);
	CHECK_FALSE(node0->getValue().compare("two"));
    }
}
