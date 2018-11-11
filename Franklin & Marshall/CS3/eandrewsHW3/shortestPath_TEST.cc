#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include"readGraph.h"
#include"shortestPath.h"

TEST_CASE("testing shortestPath") {

  SECTION("graph_network.txt") {

    SECTION("dijkstra's algorithm -- matrix") {

      std::ifstream fin("graph_network.txt");
      double** matrix;
      std::string* vLabels;
      std::string** eLabels;
      int numV = readGraph(fin, matrix, vLabels, eLabels);
      REQUIRE(numV == 4);
      double* dist;
      int* prev;
      fin.close();

      SECTION("source 0") {
        dijkstra(matrix, numV, 0, dist, prev);
      
        CHECK(dist[0] == 0);
        CHECK(dist[1] == 4.5);
        CHECK(dist[2] == 10);
        CHECK(dist[3] == 3.2);

        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 0);
      }

      SECTION("source 1") {
        dijkstra(matrix, numV, 1, dist, prev);
      
        CHECK(dist[0] == 8.2);
        CHECK(dist[1] == 0);
        CHECK(dist[2] == 5.5);
        CHECK(dist[3] == 8.4);

        CHECK(prev[0] == 2);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 2);
      }

      SECTION("source 2") {
        dijkstra(matrix, numV, 2, dist, prev);

        CHECK(dist[0] == 2.7);
        CHECK(dist[1] == 4.2);
        CHECK(dist[2] == 0);
        CHECK(dist[3] == 2.9);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[3] == 2);
      }

      SECTION("source 3") {
        dijkstra(matrix, numV, 3, dist, prev);

        CHECK(dist[0] == 9.5);
        CHECK(dist[1] == 1.3);
        CHECK(dist[2] == 6.8);
        CHECK(dist[3] == 0);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
      }
    }

    SECTION("dijkstra's algorithm -- list") {

      std::ifstream fin("graph_network.txt");
      int** adj;
      double** weights;
      int* lengths;
      std::string* vLabels;
      std::string** eLabels;
      int numV = readGraph(fin, adj, weights, lengths, vLabels, eLabels);
      REQUIRE(numV == 4);
      double* dist;
      int* prev;
      fin.close();

      SECTION("source 0") {
        dijkstra(adj, weights, lengths, numV, 0, dist, prev);
      
        CHECK(dist[0] == 0);
        CHECK(dist[1] == 4.5);
        CHECK(dist[2] == 10);
        CHECK(dist[3] == 3.2);

        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 0);
      }

      SECTION("source 1") {
        dijkstra(adj, weights, lengths, numV, 1, dist, prev);
      
        CHECK(dist[0] == 8.2);
        CHECK(dist[1] == 0);
        CHECK(dist[2] == 5.5);
        CHECK(dist[3] == 8.4);

        CHECK(prev[0] == 2);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 2);
      }

      SECTION("source 2") {
        dijkstra(adj, weights, lengths, numV, 2, dist, prev);

        CHECK(dist[0] == 2.7);
        CHECK(dist[1] == 4.2);
        CHECK(dist[2] == 0);
        CHECK(dist[3] == 2.9);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[3] == 2);
      }

      SECTION("source 3") {
        dijkstra(adj, weights, lengths, numV, 3, dist, prev);

        CHECK(dist[0] == 9.5);
        CHECK(dist[1] == 1.3);
        CHECK(dist[2] == 6.8);
        CHECK(dist[3] == 0);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
      }
    }

    SECTION("bellman-ford") {

      std::ifstream fin("graph_network.txt");
      int** edgeList;
      double* weights;
      int numE;
      std::string* vLabels;
      std::string* eLabels;
      int numV = readGraph(fin, edgeList, weights, numE, vLabels, eLabels);
      REQUIRE(numV == 4);
      double* dist;
      int* prev;
      fin.close();
      
      SECTION("source 0") {
        bellmanFord(edgeList, weights, numV, numE, 0, dist, prev);
      
        CHECK(dist[0] == 0);
        CHECK(dist[1] == 4.5);
        CHECK(dist[2] == 10);
        CHECK(dist[3] == 3.2);

        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 0);
      }

      SECTION("source 1") {
        bellmanFord(edgeList, weights, numV, numE, 1, dist, prev);
      
        CHECK(dist[0] == 8.2);
        CHECK(dist[1] == 0);
        CHECK(dist[2] == 5.5);
        CHECK(dist[3] == 8.4);

        CHECK(prev[0] == 2);
        CHECK(prev[2] == 1);
        CHECK(prev[3] == 2);
      }

      SECTION("source 2") {
        bellmanFord(edgeList, weights, numV, numE, 2, dist, prev);

        CHECK(dist[0] == 2.7);
        CHECK(dist[1] == 4.2);
        CHECK(dist[2] == 0);
        CHECK(dist[3] == 2.9);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[3] == 2);
      }

      SECTION("source 3") {
        bellmanFord(edgeList, weights, numV, numE, 3, dist, prev);

        CHECK(dist[0] == 9.5);
        CHECK(dist[1] == 1.3);
        CHECK(dist[2] == 6.8);
        CHECK(dist[3] == 0);

        CHECK(prev[0] == 2);
        CHECK(prev[1] == 3);
        CHECK(prev[2] == 1);
      }
    }

    SECTION("getting paths") {
    
      std::ifstream fin("graph_network.txt");
      double** matrix;
      std::string* vLabels;
      std::string** eLabels;
      int numV = readGraph(fin, matrix, vLabels, eLabels);
      double* dist;
      int* prev;
      dijkstra(matrix, numV, 0, dist, prev);

      int* path;
      int lenPath = getPath(0, 2, prev, path);
      CHECK(lenPath == 4);
      CHECK(path[0] == 0);
      CHECK(path[1] == 3);
      CHECK(path[2] == 1);
      CHECK(path[3] == 2);
    }
  }

  SECTION("negativeCycle.txt") {

    std::ifstream fin("negativeCycle.txt");
    int** edgeList;
    double* weights;
    int numE;
    std::string* vLabels;
    std::string* eLabels;
    int numV = readGraph(fin, edgeList, weights, numE, vLabels, eLabels);
    REQUIRE(numV == 3);
    double* dist;
    int* prev;
    fin.close();

    int test = bellmanFord(edgeList, weights, numV, numE, 0, dist, prev);

    CHECK(test != -1);
    
  } 

  SECTION("testGraph.txt") {

    SECTION("dijkstra's algorithm -- matrix") {
      std::ifstream fin("testGraph.txt");
      double** matrix;
      std::string* vLabels;
      std::string** eLabels;
      int numV = readGraph(fin, matrix, vLabels, eLabels);
      CHECK(numV == 10);
      double* dist;
      int* prev;

      SECTION("source 0") {
        dijkstra(matrix, numV, 0, dist, prev);
      }

      SECTION("source 7") {
        dijkstra(matrix, numV, 7, dist, prev);
      }
    }
  }
}
