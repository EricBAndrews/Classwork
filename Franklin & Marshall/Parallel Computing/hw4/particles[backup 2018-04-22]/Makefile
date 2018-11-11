
CC = gcc
UPCC = /usr/local/gupc/bin/upc 
#MPCC = mpicxx
OPENMP = -fopenmp
CFLAGS = -O3 -std=c99 -lm
#LIBS = -lm


TARGETS = serial serial_bin openmp autograder upc

all:	$(TARGETS)


serial: serial.o common.o
	$(CC) -o $@ $(LIBS) serial.o common.o -lm 
autograder: autograder.o common.o
	$(CC) -o $@ $(LIBS) autograder.o common.o -lm
openmp: openmp.o common.o
	$(CC) -o $@ $(LIBS) $(OPENMP) openmp.o common.o -lm
serial_bin: serial_bin.o common.o array.o
	$(CC) -o $@ $(LIBS) serial_bin.o common.o array.o -lm
upc: upc.o common_upc.o array_upc.o
	$(UPCC) -o $@ upc.o common_upc.o array_upc.o 

autograder.o: autograder.c common.h
	$(CC) -c $(CFLAGS) autograder.c -lm
openmp.o: openmp.c common.h
	$(CC) -c $(OPENMP) $(CFLAGS) openmp.c -lm
serial.o: serial.c common.h
	$(CC) -c $(CFLAGS) serial.c -lm
common.o: common.c common.h
	$(CC) -c $(CFLAGS) common.c -lm
serial_bin.o: serial_bin.c  common.h
	$(CC) -c $(CFLAGS) serial_bin.c -lm
array.o: array.c  common.h
	$(CC) -c $(CFLAGS) array.c -lm
common_upc.o: common_upc.c common_upc.h 
	$(UPCC) -c  -o common_upc.o common_upc.c 
array_upc.o: array_upc.c common_upc.h
	$(UPCC) -c  -o array_upc.o array_upc.c 
upc.o: upc.c common_upc.h
	$(UPCC) -c  upc.c 

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt
