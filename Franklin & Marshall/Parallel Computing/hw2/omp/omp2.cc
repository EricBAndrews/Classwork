#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char* argv[])
{
  //OMP started by using parallel iterative work e.g.
  
  //Things declared here are going to be shared
  int n = atoi(argv[1]);
  omp_set_num_threads(atoi(argv[2]));

  int *work_array = new int[n];
  
  #pragma omp parallel
  {
    
    //Things declared here are going to be private to the thread
    int t_id = omp_get_thread_num();
    
    printf("MyId %d \n", 
	   t_id);

    //can do loops fast
    //it will split it between threads for you 
    //how it splits is an option
    #pragma omp for
    for(int i = 0; i < n; i++)
      {
	work_array[i] = t_id;
      }

  }//end parallel block


  //We can start a parallel block and iteration at the same time
  #pragma omp parallel for
  for(int i = 0; i < n; i++)
    {
      work_array[i] = i;
    }
  
  return 0;

}
