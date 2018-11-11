CC = mpicc

all: mpi1 mpi2 mpi3 mpi4 mpi5


mpi1: mpi1.c
	$(CC) -o mpi1 mpi1.c

mpi2: mpi2.c
	$(CC) -o mpi2 mpi2.c

mpi3: mpi3.c
	$(CC) -o mpi3 mpi3.c

mpi4: mpi4.c
	$(CC) -o mpi4 mpi4.c -lm

mpi5: mpi5.c
	$(CC) -o mpi5 mpi5.c -lm

clean:  
	rm mpi1; rm mpi2; rm mpi3; rm mpi4; rm mpi5
