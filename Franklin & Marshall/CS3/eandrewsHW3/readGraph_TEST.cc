#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include"readGraph.h"

TEST_CASE("testing readGraph") {
  // i'll make it more check-heavy and less print-heavy when i've got time
  
  SECTION("read to adjacency matrix") {
    std::ifstream fin("graph_network.txt");
    double** matrix;
    std::string* vLabels;
    std::string** eLabels;
    int numV = readGraph(fin, matrix, vLabels, eLabels);
    printMatrix(matrix, 4);
    printELabels(eLabels, 4);
    CHECK(numV == 4);
    fin.close();
  }

  SECTION("read to adjacency list") {
    std::ifstream fin("graph_network.txt");
    int** adj;
    double** weights;
    int* lengths;
    std::string* vLabels;
    std::string** eLabels;
    int numV = readGraph(fin, adj, weights, lengths, vLabels, eLabels);
    std::cout << "lengths:" << std::endl;
    printArray(lengths, 4);
    std::cout << "adjacency lists:" << std::endl;
    for (int i = 0; i < 4; ++i) {
      printArray(adj[i], lengths[i]);
    }
    std::cout << "weights:" << std::endl;
    for (int i = 0; i < 4; ++i) {
      printArray(weights[i], lengths[i]);
    }
    std::cout << "edges:" << std::endl;
    for (int i = 0; i < 4; ++i) {
      printArray(eLabels[i], lengths[i]);
    }
  }

  SECTION("read to edge list") {
    std::ifstream fin("graph_network.txt");
    int** edgeList;
    double* weights;
    int numEdges;
    std::string* vLabels;
    std::string* eLabels;
    int numV = readGraph(fin, edgeList, weights, numEdges, vLabels, eLabels);
    std::cout << std::endl;
    printArray(vLabels, numV);
    printArray(eLabels, numEdges);
    for (int i = 0; i < numEdges; ++i) {
      std::cout << "[" << edgeList[i][0] << ", " << edgeList[i][1] << "]" << std::endl;
    }
    printArray(weights, numEdges);
  }
}
