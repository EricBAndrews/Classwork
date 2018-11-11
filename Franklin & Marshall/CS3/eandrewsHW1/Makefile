# general
OPTS = -Wall
DEBUG = -DDEBUG

all: encrypt decrypt keygen factorial

# unit testing
catchdebug: ReallyLongInt_Unit.cc ReallyLongInt.o
	g++ ${OPTS} -o ReallyLongIntUnit ReallyLongInt_Unit.cc ReallyLongInt.o

coverage: ReallyLongInt_Unit.cc ReallyLongInt.cc
	g++ ${OPTS} --coverage ReallyLongInt_Unit.cc ReallyLongInt.cc

# executables
encrypt: encrypt.cc numberTheory.hpp ReallyLongInt.o
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc numberTheory.hpp ReallyLongInt.o
	g++ ${OPTS} -o decrypt decrypt.cc  ReallyLongInt.o

keygen: keygen.cc numberTheory.hpp ReallyLongInt.o
	g++ ${OPTS} -o keygen keygen.cc  ReallyLongInt.o

factorial: factorial.cc ReallyLongInt.o
	g++ ${OPTS} -o factorial factorial.cc ReallyLongInt.o

# objects
numberTheory: numberTheory.hpp
	g++ ${OPTS} -c numberTheory.hpp

ReallyLongInt: ReallyLongInt.cc ReallyLongInt.hpp
	g++ ${OPTS} -c ReallyLongInt.cc

# cleanup
clean:
	rm *.o
	rm encrypt decrypt keygen factorial
