#include <iostream>
#include <limits>
#include <vector>
#include <thread>

void initialize(int start, int end, double* dist, int* prev, bool* inTree, int numThreads) {
  if (numThreads == 1) {
    for (int i = start; i < end; ++i) {
      dist[i] = std::numeric_limits<double>::infinity();
      prev[i] = 0;
      inTree[i] = false;
    }
  }
  else {
    int mid = (start + end) / 2;
    int halfThreads = numThreads / 2;
    std::thread leftThread(initialize, start, mid, dist, prev, inTree, halfThreads);
    std::thread rightThread(initialize, mid, end, dist, prev, inTree, numThreads - halfThreads);
    leftThread.join();
    rightThread.join();
  }
}

void getMinVertex(int start, int end, const double* dist, const bool* inTree, int numThreads,
                  int* minVert) {
  if (numThreads == 1) {
    double minDist = std::numeric_limits<double>::infinity();
    for (int i = start; i < end; ++i) {
      // printf("dist[%i]: %f\n", i, dist[i]);
      if (!inTree[i] && dist[i] < minDist) {
        minDist = dist[i];
        *minVert = i;
      }
    }
  }
  else {
    int leftMin = -1;
    int rightMin = -1;
    int mid = (start + end) / 2;
    int halfThreads = numThreads / 2;
    std::thread leftThread(getMinVertex, start, mid, dist, inTree, halfThreads, &leftMin);
    std::thread rightThread(getMinVertex, mid, end, dist, inTree, numThreads - halfThreads,
                            &rightMin);
    leftThread.join();
    rightThread.join();
    // printf("end: %i\n", end);
    // printf("left min: %i\nright min: %i\n", leftMin, rightMin);
    if (leftMin == -1) {
      *minVert = rightMin;
      // printf("minVert: %i", *minVert);
    }
    else if (rightMin == -1) {
      *minVert = leftMin;
      // printf("minVert: %i", *minVert);
    }
    else {
      *minVert = dist[leftMin] < dist[rightMin] ? leftMin : rightMin;
    }
  }
}

void updateDistances(int start, int end, const double* const* adjMatrix, int vert,
                     double* dist, int* prev, const bool* inTree, int numThreads) {
  if (numThreads == 1) {
    for (int i = start; i < end; ++i) {
      if (!inTree[i] && dist[vert] + adjMatrix[vert][i] < dist[i]) {
        dist[i] = dist[vert] + adjMatrix[vert][i];
        prev[i] = vert;
      }
    }
  }
  else {
    int mid = (start + end) / 2;
    int halfThreads = numThreads / 2;
    std::thread leftThread(updateDistances, start, mid, adjMatrix, vert, dist, prev, inTree,
                           halfThreads);
    std::thread rightThread(updateDistances, mid, end, adjMatrix, vert, dist, prev, inTree,
                            numThreads - halfThreads);
    leftThread.join();
    rightThread.join();
  }
}

void dijkstra(const double* const* adjMatrix, int numVertices, int source, double*& dist,
              int*& prev, int numThreads) {
  dist = new double[numVertices];
  prev = new int[numVertices];
  bool* inTree = new bool[numVertices];
  initialize(0, numVertices, dist, prev, inTree, numThreads);
  dist[source] = 0;
  for(int i = 1; i < numVertices; i++) {
    int vert = -1;
    getMinVertex(0, numVertices, dist, inTree, numThreads, &vert);
    inTree[vert] = true;
    updateDistances(0, numVertices, adjMatrix, vert, dist, prev, inTree, numThreads);
  }
  delete[] inTree;
}


int getPath(int source, int dest, const int* prev, int*& path) {
  std::vector<int> reversePath;
  int v = dest;
  while(v != source && v != -1)
  {
    reversePath.push_back(v);
    v = prev[v];
  }

  if(v == -1)
  {
    //printf("No Path Exists\n");
  }
  

  path = new int[reversePath.size()+1];
  path[0] = source;
  for(unsigned i = 1; i <= reversePath.size(); i++)
  {
    path[i] = reversePath[reversePath.size() - i];
  }

  return reversePath.size()+1;
}
