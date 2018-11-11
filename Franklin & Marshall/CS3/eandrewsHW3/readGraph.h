#ifndef READGRAPH_H
#define READGRAPH_H

#include<fstream>
#include<string>

// reads from a file stream to a matrix
int readGraph(std::ifstream& fin, double**& matrix, std::string*& vLabels,
              std::string**& eLabels);

int readGraph(std::ifstream&fin, int**& adj, double**& weights, int*& lengths,
              std::string*& vLabels, std::string**& eLabels);

int readGraph(std::ifstream& fin, int**& edgeList, double*& weights, int& numEdges,
              std::string*& vLabels, std::string*& eLabels);

// prints the various matrices. testing purposes only. too small to be worth templating
void printMatrix(double**& matrix, int size);

void printELabels(std::string**& eLabels, int size);

void printArray(int*& array, int size);

void printArray(double*& array, int size);

void printArray(std::string*& array, int size);

#endif

// emacs stuff
// Local Variables:
// mode: c++
// End:
