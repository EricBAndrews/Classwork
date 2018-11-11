#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include "RBTMultimap.h"

TEST_CASE("TESTING RBTMultimap class") {

  SECTION("constructors") {
    RBTMultimap<int, int>* tree = new RBTMultimap<int, int>();
    
    CHECK(tree->getSize() == 0);

    delete tree;

    CHECK(tree->isEmpty());
  }

  SECTION("basic functions") {
    RBTMultimap<int, std::string>* tree = new RBTMultimap<int, std::string>();
    RBTMultimap<int, int>* threeTree = new RBTMultimap<int, int>();
    
    tree->insert(1, "one");
    tree->insert(2, "two");
    tree->insert(6, "six");
    tree->insert(5, "five");
    tree->insert(4, "four");
    tree->insert(7, "seven");
    tree->insert(3, "three");
    tree->insert(8, "eight");
    tree->insert(9, "nine");
    tree->insert(10, "ten");
    tree->insert(11, "eleven");

    // nothing but threes for findFirst/findLast to have fun with
    threeTree->insert(3, 0);
    threeTree->insert(3, 1);
    threeTree->insert(3, 2);
    threeTree->insert(3, 3);
    threeTree->insert(3, 4);

    tree->printDOT("tree0.dot");

    CHECK(tree->getSize() == 11);
    CHECK_FALSE(tree->isEmpty());
    for (int i = 1; i < 12; ++i) {
      CHECK(tree->contains(i));
    }
    CHECK_FALSE(tree->contains(0));
    CHECK_FALSE(tree->contains(12));

    CHECK(tree->getMin().getKey() == 1);
    CHECK(tree->getMax().getKey() == 11);
    CHECK(threeTree->findFirst(3).getValue() == 0);
    CHECK(threeTree->findLast(3).getValue() == 4);

    threeTree->printDOT("threeTree.dot");
	    
    delete tree;
    // delete treeTree;
  }

  
  // inserts 1000 random nodes and prints them. really only useful for holistic testing, but
  // useful for finding ultra-specific errors.
  SECTION("rigorous insert") {
    RBTMultimap<int, int>* tree = new RBTMultimap<int, int>();
    for (int i = 0; i < 1000; ++i) {
      int toInsert = rand() % 1000;
      tree->insert(toInsert, 0);
      CHECK(tree->contains(toInsert));
    }

    tree->printDOT("rigIns.dot");
  }
  
  // inserts 1000 random nodes, then removes a bunch and prints them.
  SECTION("rigorous remove") {
    RBTMultimap<int, int>* tree = new RBTMultimap<int, int>();
    BSTForwardIterator<int, int> rem = BSTForwardIterator<int, int>(nullptr, nullptr);
    int oldNumItems;
    for (int i = 0; i < 10000; ++i) {
      tree->insert(rand() % 1000, 0);
    }

    for (int i = 0; i < 50000; ++i) {
      if (tree->isEmpty()) {
        break;
      }
      int toRemove = rand() % 1000;
      if (tree->contains(toRemove)) {
        oldNumItems = tree->getSize();
        rem = tree->remove(tree->findFirst(toRemove));
        CHECK(tree->getSize() == oldNumItems - 1);
      }
    }
    tree->printDOT("rigRem.dot");
  }

  SECTION("remove") {
    RBTMultimap<int, std::string>* tree = new RBTMultimap<int, std::string>();
    
    tree->insert(1, "one");
    tree->insert(2, "two");
    tree->insert(3, "three");
    tree->insert(4, "four");
    tree->insert(5, "five");
    tree->insert(6, "six");
    tree->insert(7, "seven");
    tree->insert(8, "eight");

    BSTForwardIterator<int, std::string> iterator = tree->findFirst(1);
    iterator = tree->remove(iterator);
    iterator = tree->findFirst(8);
    iterator = tree->remove(iterator);
    iterator = tree->findFirst(4);
    iterator = tree->remove(iterator);

    CHECK(tree->getSize() == 5);
    CHECK_FALSE(tree->contains(1));
    CHECK_FALSE(tree->contains(8));
    CHECK_FALSE(tree->contains(4));

    tree->printDOT("tree1.dot");
  }
}
