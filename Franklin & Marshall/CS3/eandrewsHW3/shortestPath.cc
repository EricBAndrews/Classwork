#include<limits>
#include<queue>
#include<iostream>

struct vertex {
  double dist;
  int id;
  
  bool operator<(const vertex comp) const {
    return dist > comp.dist; // backwards so priority queue is min-first
  }

  vertex(double d, int i) {
    dist = d;
    id = i;
  }
};

void dijkstra(const double* const* matrix, int numVertices, int source, double*& dist,
              int*& prev) {
  // initialize everything
  std::priority_queue<vertex, std::vector<vertex> > front;
  front.push(vertex(0, source));
  dist = new double[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    dist[i] = std::numeric_limits<double>::infinity();
  }
  dist[source] = 0;
  prev = new int[numVertices];
  // run dijkstra's
  for (int i = 0; i < numVertices; ++i) {
    if (front.empty()) {
      break;
    }
    vertex min = front.top();
    front.pop();
    for (int j = 0; j < numVertices; ++j) {
      if (min.dist + matrix[min.id][j] < dist[j]) {
        dist[j] = min.dist + matrix[min.id][j];
        prev[j] = min.id;
        front.push(vertex(dist[j], j));
      }
    }
  }
}

void dijkstra(const int* const* adj, const double* const* weights, const int* lengths,
              int numVertices, int source, double*& dist, int*& prev) {
  std::priority_queue<vertex, std::vector<vertex> > front;
  front.push(vertex(0, source));
  dist = new double[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    dist[i] = std::numeric_limits<double>::infinity();
  }
  dist[source] = 0;
  prev = new int[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    vertex min = front.top();
    front.pop();
    for (int j = 0; j < lengths[min.id]; ++j) {
      int adjacent = adj[min.id][j];
      if (min.dist + weights[min.id][j] < dist[adjacent]) {
        dist[adjacent] = min.dist + weights[min.id][j];
        prev[adjacent] = min.id;
        front.push(vertex(dist[adjacent], adjacent));
      }
    }
  }
}

int bellmanFord(const int* const* edges, const double* weights, int numVertices, int numEdges,
                int source, double*& dist, int*& prev) {
  // initialize stuff
  dist = new double[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    dist[i] = std::numeric_limits<double>::infinity();
  }
  dist[source] = 0;
  prev = new int[numVertices];
  // relax everything
  for (int i = 0; i < numEdges - 1; ++i) {
    for (int j = 0; j < numEdges; ++j) {
      if (dist[edges[j][0]] + weights[j] < dist[edges[j][1]]) {
        dist[edges[j][1]] = dist[edges[j][0]] + weights[j];
        prev[edges[j][1]] = edges[j][0];
      }
    }
  }
  // check for negative cycles
  for (int i = 0; i < numEdges; ++i) {
    if (dist[edges[i][1]] < dist[edges[i][0]] + weights[i]) {
      return edges[i][0];
    }
  }
  return -1;
}

int getPath(int source, int dest, const int* prev, int*& path) {
  int cur = dest;
  int count = 1;
  while (cur != source) {
    cur = prev[cur];
    ++count;
  }
  path = new int[count];
  cur = dest;
  for (int i = count - 1; i >= 0; --i) {
    path[i] = cur;
    cur = prev[cur];
  }
  return count;
}

int getCycle(int vertex, const int* prev, int numVertices, int*& cycle) {
  std::vector<int> cycleVec;
  // cycleVec.push_back(vertex);
  int cur = prev[vertex];
  int cycleSize = 1;
  while (cur != vertex) {
    cycleVec.push_back(cur);
    cur = prev[cur];
    ++cycleSize;
  }
  cycleVec.push_back(vertex);
  cycle = new int[cycleSize];
  for (int i = 0; i < cycleSize; ++i) {
    cycle[i] = cycleVec.back();
    cycleVec.pop_back();
  }
  return cycleSize;
}
