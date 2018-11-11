#ifndef OMP_PARALLEL_DIJKSTRA_H
#define OMP_PARALLEL_DIJKSTRA_H

void dijkstra(const double* const * adjMatrix, int numVertices, int source, double*& dist, int*& prev, int numThreads);


int getPath(int source, int dest, const int* prev, int*& path);


#endif
