#define CATCH_CONFIG_MAIN
#include"catch.hpp"
#include<iostream>

#include"binaryHeap.h"

TEST_CASE("testing binaryHeap") {

  SECTION("basic functions") {
    double* priorities = new double[5];
    priorities[0] = 5;
    priorities[1] = 3;
    priorities[2] = 1;
    priorities[3] = 2;
    priorities[4] = 4;
    BinaryHeap testHeap = BinaryHeap(priorities, 5);
    
    CHECK(testHeap.contains(1));
    CHECK_FALSE(testHeap.contains(-1));
    CHECK_FALSE(testHeap.contains(5));

    testHeap.decreasePriority(2, 2);
    CHECK(testHeap.getPriority(2) == 2);
    // for (int i = 1; i < 6; ++i) {
    //   std::cout << testHeap.getPriority(i) << " ";
    // }
    // std::cout << std::endl;
    
    testHeap.decreasePriority(5, 3);
    CHECK(testHeap.getPriority(5) == 3);
    // for (int i = 1; i < 6; ++i) {
    //   std::cout << testHeap.getPriority(i) << " ";
    // }
    // std::cout << std::endl;
    
    testHeap.decreasePriority(1, 4);
    CHECK(testHeap.getPriority(1) == 4);
    // for (int i = 1; i < 6; ++i) {
    //   std::cout << testHeap.getPriority(i) << " ";
    // }
    // std::cout << std::endl;
    
    testHeap.decreasePriority(3, 0);
    CHECK(testHeap.getPriority(3) == 0);
    // for (int i = 1; i < 6; ++i) {
    //   std::cout << testHeap.getPriority(i) << " ";
    // }
    // std::cout << std::endl;
    
    testHeap.decreasePriority(4, 1);
    CHECK(testHeap.getPriority(4) == 1);
    // for (int i = 1; i < 6; ++i) {
    //   std::cout << testHeap.getPriority(i) << " ";
    // }
    // std::cout << std::endl;
    
    for (int i = 0; i < 5; ++i) {
      CHECK(testHeap.getPriority(testHeap.getMin()) == i);
      testHeap.popMin();
    }
  }
}
