#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  omp_set_num_threads(atoi(argv[1]));
  printf("Before a parallel block\n");
  #pragma omp parallel
  {
    //A parallel block is made
    //This parallel block can be thought of as a threadpool

    printf("Thread: %d Inside a parallel block\n",
	   omp_get_thread_num());

  }
}
