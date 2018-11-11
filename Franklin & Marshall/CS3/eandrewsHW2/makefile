CC = g++
CFLAGS = -Wall
COVERAGE = --coverage
OPTIONS=-std=c++11

all: schedulesim

main: schedulesim

test: ArrayListUnit LinkedListUnit IOBoundProcessUnit RoundRobinUnit FastRoundRobinUnit CompletelyFairUnit SchedulerUnit BSTNodeUnit BSTMultimapUnit RBTMultimapUnit

coverage: ArrayListCoverage LinkedListCoverage IOBoundProcessCoverage RoundRobinCoverage FastRoundRobinCoverage CompletelyFairCoverage SchedulerCoverage BSTNodeCoverage BSTMultimapCoverage RBTMultimapCoverage

# objects
Scheduler.o: Scheduler.cc
	$(CC) $(CFLAGS) -c Scheduler.cc

Process.o: Process.cc
	$(CC) $(CFLAGS) -c Process.cc

simulate.o: simulate.cc
	$(CC) $(CFLAGS) $(OPTIONS) -c simulate.cc

# executables
schedulesim: schedulesim.cc simulate.o Scheduler.o Process.o
	$(CC) $(CFLAGS) $(OPTIONS) -o schedulesim schedulesim.cc simulate.o Scheduler.o Process.o

# unit tests
ArrayListUnit: ArrayList_TEST.cc ArrayList.h
	$(CC) $(CFLAGS) -o ArrayListUnit ArrayList_TEST.cc

LinkedListUnit: LinkedList_TEST.cc LinkedList.h
	$(CC) $(CFLAGS) -o LinkedListUnit LinkedList_TEST.cc

IOBoundProcessUnit: IOBoundProcess_TEST.cc Process.o
	$(CC) $(CFLAGS) -o IOBBoundProcessUnit IOBoundProcess_TEST.cc Process.o

RoundRobinUnit: RoundRobin_TEST.cc Scheduler.o Process.o
	$(CC) $(CFLAGS) -o RoundRobinUnit RoundRobin_TEST.cc Scheduler.o Process.o

FastRoundRobinUnit: FastRoundRobin_TEST.cc Scheduler.o Process.o
	$(CC) $(CFLAGS) -o FastRoundRobinUnit FastRoundRobin_TEST.cc Scheduler.o Process.o

CompletelyFairUnit: CompletelyFair_TEST.cc Scheduler.o Process.o
	$(CC) $(CFLAGS) -o CompletelyFairUnit CompletelyFair_TEST.cc Scheduler.o Process.o

SchedulerUnit: Scheduler_TEST.cc Scheduler.o Process.o
	$(CC) $(CFLAGS) -o SchedulerUnit Scheduler_TEST.cc Scheduler.o Process.o

BSTNodeUnit: BSTNode_TEST.cc BSTNode.h
	$(CC) $(CFLAGS) -o BSTNodeUnit BSTNode_TEST.cc

BSTMultimapUnit: BSTMultimap_TEST.cc BSTMultimap.h BSTForwardIterator.h
	$(CC) $(CFLAGS) -o BSTMultimapUnit BSTMultimap_TEST.cc

RBTMultimapUnit: RBTMultimap_TEST.cc RBTMultimap.h
	$(CC) $(CFLAGS) -o RBTMultimapUnit RBTMultimap_TEST.cc

# coverage tests
ArrayListCoverage: ArrayList_TEST.cc ArrayList.h
	$(CC) $(CFLAGS) $(COVERAGE) ArrayList_TEST.cc

LinkedListCoverage: LinkedList_TEST.cc LinkedList.h
	$(CC) $(CFLAGS) $(COVERAGE) LinkedList_TEST.cc

IOBoundProcessCoverage: IOBoundProcess_TEST.cc Process.o
	$(CC) $(CFLAGS) $(COVERAGE) IOBoundProcess_TEST.cc Process.o

RoundRobinCoverage: RoundRobin_TEST.cc Scheduler.cc Process.o
	$(CC) $(CFLAGS) $(COVERAGE) RoundRobin_TEST.cc Scheduler.cc Process.o

FastRoundRobinCoverage: FastRoundRobin_TEST.cc Scheduler.cc Process.o
	$(CC) $(CFLAGS) $(COVERAGE) FastRoundRobin_TEST.cc Scheduler.cc Process.o

CompletelyFairCoverage: CompletelyFair_TEST.cc Scheduler.cc Process.o
	$(CC) $(CFLAGS) $(COVERAGE) CompletelyFair_TEST.cc Scheduler.cc Process.o

SchedulerCoverage: Scheduler_TEST.cc Scheduler.cc Process.o
	$(CC) $(CFLAGS) $(COVERAGE) Scheduler_TEST.cc Scheduler.cc Process.o

BSTNodeCoverage: BSTNode_TEST.cc
	$(CC) $(CFLAGS) $(COVERAGE) BSTNode_TEST.cc

BSTMultimapCoverage: BSTMultiMap_TEST.cc
	$(CC) $(CFLAGS) $(COVERAGE) BSTMultiMap_TEST.cc

RBTMultimapCoverage: RBTMultimap_TEST.cc
	$(CC) $(CFLAGS) $(COVERAGE) RBTMultimap_TEST.cc

clean:
	rm *.o; rm *.gcno; rm *.gcda; rm *Unit; rm ArrayListUnit; rm ProcessUnit; rm SchedulerUnit; rm LinkedListUnit; rm schedulesim; rm a.out
