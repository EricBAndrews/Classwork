CC=g++-6
OPT=-std=c++11 -pthread 


all: runOmpParallelDijkstra


readGraph.o: readGraph.cc readGraph.h
	$(CC) $(OPT) -c readGraph.cc

ompParallelDijkstra.o: ompParallelDijkstra.h ompParallelDijkstra.cc
	$(CC) $(OPT) -c ompParallelDijkstra.cc -fopenmp

runOmpParallelDijkstra: runOmpParallelDijkstra.cc ompParallelDijkstra.o readGraph.o
	$(CC) $(OPT) -o runOmpParallelDijkstra runOmpParallelDijkstra.cc ompParallelDijkstra.o readGraph.o -fopenmp


clean:
	rm *.o;  rm runOmpParallelDijkstra;
