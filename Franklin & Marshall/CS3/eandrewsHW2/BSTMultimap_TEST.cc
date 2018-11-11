#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include"BSTNode.h"
#include<string>

#include"BSTMultimap.h"

TEST_CASE("TESTING BSTMultimap class") {

  SECTION("constructors") {
    BSTMultimap<int, std::string>* tree = new BSTMultimap<int, std::string>();
	
    CHECK(tree->getSize() == 0);

    delete tree;

    CHECK(tree->isEmpty());
  }
    
  SECTION("basic functions") {
    BSTMultimap<int, std::string>* tree = new BSTMultimap<int, std::string>();

    tree->insert(4, "four");
    tree->insert(2, "two");
    tree->insert(6, "six");
    tree->insert(1, "one");
    tree->insert(3, "three");
    tree->insert(5, "five");
    tree->insert(7, "seven");
    tree->insert(8, "eight");

    // tree->printTree();

    CHECK(tree->getSize() == 8);
    CHECK_FALSE(tree->isEmpty());
    for (int i = 1; i < 9; ++i) {
      CHECK(tree->contains(i));
    }
    CHECK_FALSE(tree->contains(0));
    CHECK_FALSE(tree->contains(10));
	    
    delete tree;
  }

  SECTION("iterator") {
    BSTMultimap<int, int>* tree = new BSTMultimap<int, int>();

    for (int i = 0; i < 25; ++i) {
      tree->insert(i, i);
    }

    BSTForwardIterator<int, int> iterator = tree->getMin();

    CHECK_FALSE(iterator.isPastEnd());
	
    for (int i = 0; i < 25; ++i) {
      CHECK(iterator.getKey() == i);
      iterator.next();
    }
    CHECK(iterator.isPastEnd());
    iterator = tree->findFirst(5);
    CHECK(iterator.getKey() == 5);
    iterator = tree->findLast(5);
    CHECK(iterator.getKey() == 5);
    iterator = tree->findLast(24);
    CHECK(iterator.getKey() == 24);

    delete tree;
  }
  
  // inserts 1000 random nodes and prints them. really only useful for holistic testing, but
  // useful for finding ultra-specific errors.
  SECTION("rigorous insert") {
    BSTMultimap<int, int>* tree = new BSTMultimap<int, int>();
    for (int i = 0; i < 1000; ++i) {
      // int toInsert = rand() % 1000;
      int toInsert = i;
      tree->insert(toInsert, 0);
      CHECK(tree->contains(toInsert));
    }
    
    // tree->printTree();
    // BSTForwardIterator<int, int> iterator = tree->getMin();
    // for (int i = 0; i < 50000; ++i) {
    //   CHECK(iterator.getKey() == i);
    //   iterator.next();
    // }
  }

  SECTION("remove") {
    BSTMultimap<int, std::string>* tree = new BSTMultimap<int, std::string>();

    tree->insert(4, "four");
    tree->insert(2, "two");
    tree->insert(6, "six");
    tree->insert(1, "one");
    tree->insert(3, "three");
    tree->insert(5, "five");
    tree->insert(7, "seven");
    tree->insert(8, "eight");

    BSTForwardIterator<int, std::string> iterator = tree->findFirst(4);
	
    iterator = tree->remove(iterator);

    // tree->printTree();
    
    // for (int i = 0; i < 6; ++i) {
    //   iterator.next();
    // }
    // iterator = tree->remove(iterator);
    // iterator = tree->getMin();
    // for (int i = 0; i < 2; ++i) {
    //   iterator.next();
    // }

    // iterator = tree->remove(iterator);

    // CHECK(tree->getSize() == 5);
    // CHECK_FALSE(tree->contains(1));
    // CHECK_FALSE(tree->contains(8));
    // CHECK_FALSE(tree->contains(4));

    // std::cout << "tree after removals:" << std::endl;
    // tree->printTree();
  }
}
