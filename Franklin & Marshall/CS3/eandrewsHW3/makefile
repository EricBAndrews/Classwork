CC = g++
CLANG = clang++ # for os x compilation
CFLAGS = -Wall
COVERAGE = --coverage
OPTIONS = -std=c++11
THREAD = -pthread

# executables
matrixDijkstra: matrixDijkstra.cc readGraph.o shortestPath.o
	$(CC) $(CFLAGS) $(OPTIONS) -o matrixDijkstra matrixDijkstra.cc readGraph.o shortestPath.o

listDijkstra: listDijkstra.cc readGraph.o shortestPath.o
	$(CC) $(CFLAGS) $(OPTIONS) -o listDijkstra listDijkstra.cc readGraph.o shortestPath.o

bellmanFord: bellmanFord.cc readGraph.o shortestPath.o
	$(CC) $(CFLAGS) $(OPTIONS) -o bellmanFord bellmanFord.cc readGraph.o shortestPath.o

runTemplateParallelDijkstra: runTemplateParallelDijkstra.cc templateParallelDijkstra.o readGraph.o
	$(CC) $(CFLAGS) $(OPTIONS) -o runTemplateParallelDijkstra runTemplateParallelDijkstra.cc templateParallelDijkstra.o readGraph.o

# objects
readGraph.o: readGraph.cc readGraph.h
	$(CC) $(CFLAGS) -c readGraph.cc

shortestPath.o: shortestPath.cc shortestPath.h
	$(CC) $(CFLAGS) -c shortestPath.cc

binaryHeap.o: binaryHeap.cc binaryHeap.h
	$(CC) $(CFLAGS) -c binaryHeap.cc

# !!!IMPORTANT!!! IF THIS DOES NOT COMPILE CHANGE 'CLANG' TO 'CC'
templateParallelDijkstra.o: templateParallelDijkstra.cc templateParallelDijkstra.h
	$(CLANG) $(CFLAGS) $(OPTIONS) -c templateParallelDijkstra.cc

# unit tests
readGraphUnit: readGraph_TEST.cc readGraph.o
	$(CC) $(CFLAGS) -o readGraphUnit readGraph_TEST.cc readGraph.o

shortestPathUnit: shortestPath_TEST.cc shortestPath.o readGraph.o
	$(CC) $(CFLAGS) -o shortestPathUnit shortestPath_TEST.cc shortestPath.o readGraph.o

binaryHeapUnit: binaryHeap_TEST.cc binaryHeap.o
	$(CC) $(CFLAGS) -o binaryHeapUnit binaryHeap_TEST.cc binaryHeap.o

# coverage

readGraphCoverage: readGraph_TEST.cc readGraph.cc
	$(CC) $(CFLAGS) $(COVERAGE) readGraph_TEST.cc readGraph.cc

shortestPathCoverage: shortestPath_TEST.cc shortestPath.cc readGraph.cc
	$(CC) $(CFLAGS) $(COVERAGE) shortestPath_TEST.cc shortestPath.cc readGraph.cc

binaryHeapCoverage: binaryHeap_TEST.cc binaryHeap.cc
	$(CC) $(CFLAGS) $(COVERAGE) binaryHeap_TEST.cc binaryHeap.cc
