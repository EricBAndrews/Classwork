#ifndef TEMPLATE_PARALLEL_DIJSKTRA_H
#define TEMPLATE_PARALLEL_DIJSKTRA_H

void dijkstra(const double* const * adjMatrix, int numVertices, int source, double*& dist,
	      int*& prev, int numThreads);

int getPath(int source, int dest, const int* prev, int*& path);

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
