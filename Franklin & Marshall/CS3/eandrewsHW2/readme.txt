Eric Andrews
Project 2: Process Scheduler
= = = = = = = = = = = = = = = =
FILES
- - - - - - - -
primary:
simulate.cc
Process.cc
Scheduler.cc
schedulesim.cc
simulate.h
Process.h
Scheduler.h
List.h
ArrayList.h
LinkedListNode.h
LinkedList.h
BBSTNode.h
BSTMultimap.h
BSTForwardIterator.h
RBTNode.h
RBTMultimap.h
makefile

secondary:
ArrayList_TEST.cc
Process_TEST.cc
IOBoundProcess_TEST.cc
Scheduler_TEST.cc
LinkedList_TEST.cc
RoundRobin
FastRoundRobin_TEST.cc
BSTNode_TEST.cc
BSTMultimap_TEST.cc
CompletelyFair_TEST.cc
RBTMultimap_TEST.cc
catch.hpp

other:
readme.txt
timing.pdf
cputimes.pdf
cover.docx
= = = = = = = = = = = = = = = =
INSTRUCTIONS
- - - - - - - -
invoking `make' will compile schedulesim; invoking `make test' will compile all unit tests, and invoking `make coverage' will compile the unit tests with coverage. invoking `make [filename]Unit' will compile only that file's unit test; invoking `make [filename]Coverage' will compile only that file's unit test with coverage.

schedulesim:
schedulesim simulates running the given number of cycles with four different schedulers (round robin, fast round robin, completely fair, fast completely fair) and prints statistics about each one.
schedulesim takes 3 command line arguments: the number of cpu-bound processes, the number of io-bound processes, and the number of cycles.

[filename]Unit:
runs the unit tests in [filename]_TEST.cc.
= = = = = = = = = = = = = = = =
KNOWN ISSUES
- - - - - - - -
Completely Fair returns very strange data, most likely due to an error in BSTMultimap.h. it segfaults over 8000 cycles, so there is no data over that. Fast Completely Fair, however, works fine.
