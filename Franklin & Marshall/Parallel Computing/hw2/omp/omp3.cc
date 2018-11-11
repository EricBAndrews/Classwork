#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
  
  int n = atoi(argv[1]);
  omp_set_num_threads(atoi(argv[2]));

  int *array = new int[n];

  //Fill array
  #pragma omp parallel
  {
    srand(int(time(NULL))^omp_get_thread_num());
    
    #pragma omp for
    for(int i = 0; i < n; i++)
      {
	array[i] = rand() % (n+1);
      }
  }//end paralle block

  int x = 999999;
  double tic = omp_get_wtime();
  #pragma omp parallel for reduction(min:x)
  for(int i = 0; i < n; i++)
    {
      if(array[i] < x)
	{
	  x = array[i];
	}
    }
  double toc = omp_get_wtime();
  printf("Time to find min: %f \n",
	 toc-tic);

  return 0;
}
