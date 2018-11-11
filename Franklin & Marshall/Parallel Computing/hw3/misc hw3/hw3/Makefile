# On Bridges we will check versus your performance versus Intel MKL library's BLAS. 

CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
#MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
#LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm
#LDLIBS = -lrt  -I$(MKLROOT)/include -Wl,-L$(MKLROOT)/lib/intel64/ -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread -lm -ldl
LDLIBS = -lblas  -lm -ldl

targets = benchmark-naive benchmark-blocked benchmark-blas benchmark-cuda benchmark-openacc
objects = benchmark.o dgemm-naive.o dgemm-blocked.o dgemm-blas.o dgemm-cuda-blocked.o dgemm-openacc-blocked.o

.PHONY : default
default : all

.PHONY : all
all : clean $(targets)

benchmark-naive : benchmark.o dgemm-naive.o 
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-blocked : benchmark.o dgemm-blocked.o
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-blas : benchmark.o dgemm-blas.o
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-cuda : benchmark-cuda.cu dgemm-cuda-blocked.cu
	nvcc -o $@ $^ $(LDLIBS)
benchmark-openacc : benchmark-openacc.o dgemm-openacc-blocked.o
	pgcc -acc -o $@ $^  $(LDLIBS)
benchmark-cuda.o : benchmark-cuda.cu
	nvcc -c -o benchmark-cuda.o benchmark-cuda.cu 
benchmark-openacc.o : benchmark.c
	pgcc -acc -c -o benchmark-openacc.o benchmark.c 
dgemm-naive.o : dgemm-naive.c
	$(CC) -c $(CFLAGS) dgemm-naive.c
dgemm-blocked : dgemm-blocked.c
	$(CC) -c $(CFLAGS) dgemm-blocked.c
dgemm-blas : dgemm-blas.c
	$(CC) -c $(CFLAGS) dgemm-blas.c
benchmark.o : benchmark.c
	$(CC) -c $(CFLAGS) benchmark.c
dgemm-cuda-blocked.o : dgemm-cuda-blocked.cu
	nvcc -c dgemm-cuda-blocked.cu
dgemm-openacc-blocked.o : dgemm-openacc-blocked.c
	pgcc -acc -c dgemm-openacc-blocked.c

#%.o : %.c
#	$(CC) -c $(CFLAGS) $<

.PHONY : clean
clean:
	rm -f $(targets) $(objects) *.stdout
