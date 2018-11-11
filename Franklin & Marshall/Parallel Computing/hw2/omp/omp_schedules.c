#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include "omp.h"

#define N 20
//#define P 4
#define CHUNK 1

void print_omp_info(char *s, int i)
{
  printf("%s Thread: %d doing interation %d \n", 
	 s, omp_get_thread_num(), i);
}

int main(int argc, char* argv[])
{

  int P = atoi(argv[1]);
  
#pragma omp parallel for schedule(static) num_threads(P)
  for(int i = 0; i < N; i++)
    {
      print_omp_info("static", i);
    }
  
#pragma omp parallel for schedule(dynamic, CHUNK) num_threads(P)
  for(int i = 0; i < N; i++)
    {
      print_omp_info("dynamic", i);
    }

#pragma omp parallel for schedule(guided, CHUNK) num_threads(P)
  for(int i = 0; i < N; i++)
    {
      print_omp_info("guided" , i);
    }
  
  
#pragma omp parallel for num_threads(P)
  for(int i = 0; i < N; i++)
    {
      print_omp_info("exp", i);
    }


  return 0;

}//end main


