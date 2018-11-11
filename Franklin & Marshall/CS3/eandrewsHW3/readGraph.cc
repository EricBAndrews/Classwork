#include<limits>
#include<iostream>
#include<fstream>
#include<vector>

#include"readGraph.h"

int readGraph(std::ifstream&fin, double**& matrix, std::string*& vLabels,
              std::string**& eLabels) {
  int numV, numE; // number of vertices, edges
  int source, dest; // for reading into matrix
  double weight;
  std::string name; // for reading into vLabels, eLabels
  fin >> numV >> numE;
  // create arrays
  matrix = new double*[numV];
  eLabels = new std::string*[numV];
  vLabels = new std::string[numV];
  // initialize inner arrays
  for (int i = 0; i < numV; ++i) {
    matrix[i] = new double[numV];
    eLabels[i] = new std::string[numV];
    // set matrix values to infinity
    for (int j = 0; j < numV; ++j) {
      if (i == j) {
        matrix[i][j] = 0;
      }
      else {
        matrix[i][j] = std::numeric_limits<double>::infinity();
      }
    }
    // read vertex names into vLabels
    fin >> name;
    vLabels[i] = name;
  }
  // read weights and names into eLabels
  for (int i = 0; i < numE; ++i) {
    fin >> source;
    fin >> dest;
    fin >> weight;
    fin.get(); // skip whitespace
    std::getline(fin, name); // gets nothing if name doesn't exist; otherwise gets name
    matrix[source][dest] = weight;
    eLabels[source][dest] = name;
  }
  return numV;
}

int readGraph(std::ifstream&fin, int**& adj, double**& weights, int*& lengths,
              std::string*& vLabels, std::string**& eLabels) {
  int numV, numE; // number of vertices, edges
  int source, dest;
  double weight;
  std::string name; // for reading into eLabels, vLabels
  // read number of vertices, edges, vertex names
  fin >> numV >> numE;
  // initialize arrays
  adj = new int*[numV];
  weights = new double*[numV];
  lengths = new int[numV];
  vLabels = new std::string[numV];
  eLabels = new std::string*[numV];
  // initialize lengths, vLabels
  for (int i = 0; i < numV; ++i) {
    lengths[i] = 0;
    fin >> name;
    vLabels[i] = name;
  }
  // initialize vectors for dynamic arrays
  std::vector<int>* adjVect = new std::vector<int>[numV];
  std::vector<double>* weightsVect = new std::vector<double>[numV];
  std::vector<std::string>* eLabelsVect = new std::vector<std::string>[numV];
  // read graph data
  for (int i = 0; i < numE; ++i) {
    // read into adjacency matrix, weight matrix
    fin >> source;
    fin >> dest;
    fin >> weight;
    adjVect[source].push_back(dest);
    weightsVect[source].push_back(weight);
    ++(lengths[source]);
    // read into edge matrix
    fin.get();
    std::getline(fin, name);
    eLabelsVect[source].push_back(name);
  }
  // translate vectors into arrays
  for (int i = 0; i < numV; ++i) {
    adj[i] = adjVect[i].data();
    weights[i] = weightsVect[i].data();
    eLabels[i] = eLabelsVect[i].data();
  }
  return numV;
}

int readGraph(std::ifstream& fin, int**& edgeList, double*& weights, int& numEdges,
              std::string*& vLabels, std::string*& eLabels) {
  int numV;
  int source, dest;
  double weight;
  std::string name;
  fin >> numV >> numEdges;
  edgeList = new int*[numEdges];
  weights = new double[numEdges];
  vLabels = new std::string[numV];
  eLabels = new std::string[numEdges];
  for (int i = 0; i < numV; ++i) {
    fin >> name;
    vLabels[i] = name;
  }
  for (int i = 0; i < numEdges; ++i) {
    fin >> source;
    fin >> dest;
    fin >> weight;
    fin.get();
    std::getline(fin, name);
    edgeList[i] = new int[2];
    edgeList[i][0] = source;
    edgeList[i][1] = dest;
    weights[i] = weight;
    eLabels[i] = name;
  }
  return numV;
}

void printMatrix(double**& matrix, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << "[" <<  matrix[i][j] << "]";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void printELabels(std::string**& eLabels, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << "[" <<  eLabels[i][j] << "]";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void printArray(int*& array, int size) {
  std::cout << "[ ";
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;
}

void printArray(double*& array, int size) {
  std::cout << "[ ";
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;
}

void printArray(std::string*& array, int size) {
  std::cout << "[ ";
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << "]" << std::endl;
}
