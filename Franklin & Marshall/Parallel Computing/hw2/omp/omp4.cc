#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 999

int main(int argc, char* argv[])
{

  omp_set_num_threads(atoi(argv[1]));
  int sum = 0;



  #pragma omp parallel for
  for(int i = 0 ; i < NUM; i++)
    {
      #pragma omp critical
      {
	//Critical blocks allows only 1 thread at a time to enter
	//This is like our locks
	//OMP also has atomics (we will not cover those)
	sum +=1;
      }

    }

  #pragma omp parallel
  {

    #pragma omp master
    {
      //Only the master thread can go into here (i.e., id == 0)
      printf("Master says sum is: %d \n",
	     sum);
    }
    
    #pragma omp single
    {
      //Only 1 thread can ever go in here, we don't care which one
      printf("Some thread says sum is: %d \n",
	     sum);
    }

  }
  return 0;

}
