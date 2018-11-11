CC = g++-6
OPTS = -std=c++11 -fopenmp

all: omp1 omp2 omp3 omp4 omp_schedules

omp1: omp1.cc
	$(CC) $(OPTS) -o omp1 omp1.cc

omp2: omp2.cc
	$(CC) $(OPTS) -o omp2 omp2.cc

omp3: omp3.cc
	$(CC) $(OPTS) -o omp3 omp3.cc

omp4: omp4.cc 
	$(CC) $(OPTS) -o omp4 omp4.cc

omp_schedules: omp_schedules.c
	$(CC) -std=c99 -o omp_schedules omp_schedules.c -fopenmp
clean:
	rm omp1; rm omp2; rm omp3; rm omp4; rm omp_schedules;
