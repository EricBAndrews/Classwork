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
  double** matrix;
  std::string* vLabels;
  std::string** eLabels;
  int numV = readGraph(fin, matrix, vLabels, eLabels);
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
  dijkstra(matrix, numV, source, dist, prev);
  auto end = std::chrono::system_clock::now();
  auto durMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  int* path;
  int pathLen = getPath(source, dest, prev, path);

  // output
  std::cout << "total weight of shortest path: " << dist[dest] << std::endl;
  std::cout << "elapsed time: " << double(durMS.count()) << "ms" << std::endl;
  std::ofstream fout(argv[2]);
  fout << numV << " " << pathLen - 1 << "\n";
  for (int i = 0; i < numV; ++i) {
    fout << vLabels[i] << "\n";
  }
  for (int i = 0; i < pathLen - 1; ++i) {
    fout << path[i] << " " << path[i+1] << " " << matrix[path[i]][path[i+1]] << " "
         << eLabels[path[i]][path[i+1]] << "\n";
  }
  fout.close();
  return 0;
}
