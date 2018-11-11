#include<fstream>
#include<iostream>
#include<chrono>

#include"shortestPath.h"
#include"readGraph.h"

int main(int argc, char** argv) {
  /* arguments:
     graph file
     output file
     source vertex
     dest vertex */
  if (argc != 5) {
    std::cout << "invalid number of arguments (expected 4, got " << argc - 1 << "); exiting."
              << std::endl;
    return 1;
  }

  // create matrix
  std::ifstream fin(argv[1]);
  int** edgeList;
  double* weights;
  int numE;
  std::string* vLabels;
  std::string* eLabels;
  int numV = readGraph(fin, edgeList, weights, numE, vLabels, eLabels);
  fin.close();

  // parse source, dest
  int source = -1;
  for (int i = 0; i < numV; ++i) {
    if (!vLabels[i].compare(argv[3])) {
      source = i;
      break;
    }
  }
  if (source == -1) {
    std::cout << "invalid source vertex (" << argv[3] << "); exiting." << std::endl;
    return 1;
  }
  int dest = -1;
  for (int i = 0; i < numV; ++i) {
    if (!vLabels[i].compare(argv[4])) {
      dest = i;
      break;
    }
  }
  if (dest == -1) {
    std::cout << "invalid destination vertex (" << argv[4] << "); exiting." << std::endl;
    return 1;
  }

  // dijkstra, then get path on the matrix
  double* dist;
  int* prev;
  auto start = std::chrono::system_clock::now(); // gets start time
  int vertex = bellmanFord(edgeList, weights, numV, numE, source, dist, prev);
  auto end = std::chrono::system_clock::now();
  auto durMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  // output
  if (vertex == -1) {
    int* path;
    int pathLen = getPath(source, dest, prev, path);
    std::cout << "total weight of shortest path: " << dist[dest] << std::endl;
    std::cout << "elapsed time: " << double(durMS.count()) << "ms" << std::endl;
    std::ofstream fout(argv[2]);
    fout << numV << " " << pathLen - 1 << "\n";
    for (int i = 0; i < numV; ++i) {
      fout << vLabels[i] << "\n";
    }
    for (int i = 0; i < pathLen - 1; ++i) {
      int pathSource = path[i];
      int pathDest = path[i+1];
      int j = 0;
      for (int j = 0; j < numE; ++j) {
        if (edgeList[j][0] == pathSource && edgeList[j][1] == pathDest) {
          break;
        }
      }
      fout << pathSource << " " << pathDest << " " << weights[j] << " "
           << eLabels[j] << "\n";
    }
    fout.close();
  }
  else {
    int* cycle;
    int cycleLen = getCycle(vertex, prev, numV, cycle);
    double cycleWeight = 0;
    int* cycleWeights = new int[cycleLen - 1];
    for (int i = 0; i < cycleLen; ++i) {
      for (int j = 0; j < numV; ++j) {
        if (edgeList[j][0] == cycle[i] && edgeList[j][i] == cycle[i+1]) {
          cycleWeights[i] = weights[j];
          cycleWeight += weights[j];
          break;
        }
      }
    }
    std::cout << "negative cycle detected with weight " << cycleWeight << std::endl;
    std::cout << "elapsed time: " << double(durMS.count()) << "ms" << std::endl;
    std::ofstream fout(argv[2]);
    fout << numV << " " << cycleLen << "\n";
    for (int i = 0; i < numV; ++i) {
      fout << vLabels[i] << "\n";
    }
    for (int i = 0; i < cycleLen; ++i) {
      fout << cycle[i] << " " << cycle[i+1] << " " << cycleWeights[i] << " "
           << vLabels[cycle[i]] << "->" << vLabels[cycle[i+1]] << "\n";
    }
    fout.close();
  }
  return 0;
}
