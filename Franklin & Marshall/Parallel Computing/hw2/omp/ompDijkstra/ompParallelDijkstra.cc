
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <climits> //used to for the max in getMin (faster than C++ limit call)

inline
void t_initialize(int start, int end, double* dist, int* prev, bool* inTree)
{
 
#pragma omp for 
  for(int i = start; i < end; i++)
    {
      dist[i] = std::numeric_limits<double>::infinity();
      prev[i] = -1;
      inTree[i] = false;
    }
}// end t_init

struct MinCompare
{
  double dist;
  int loc;
  MinCompare()
  {
    dist = std::numeric_limits<double>::infinity();
    loc = -1;
  }
};

MinCompare& myCompare(MinCompare &x, MinCompare &y)
{
  if(x.dist == y.dist)
    {
      if(x.loc == -1)
	{
	  return y;
	}
      else
	{
	  return x;
	}
    }
  else
    {
      if(x.dist <= y.dist)
	{
	  return x;
	}
      else
	{
	  return y;
	}
    }

}

//#pragma omp declare reduction(minimum : MinCompare : omp_out = omp_in.dist <= omp_out.dist ? omp_in : omp_out) initializer (omp_priv = MinCompare())

#pragma omp declare reduction(minimum : MinCompare : omp_out = myCompare(omp_in, omp_out)) initializer (omp_priv = MinCompare())



void dijkstra(const double* const * adjMatrix, int numVertices, int source, double*& dist, int*& prev,  int numThreads)
{

   dist = new double[numVertices];
   prev = new int[numVertices];
   bool* inTree = new bool[numVertices];
   
   MinCompare min;
   min.dist = std::numeric_limits<double>::infinity();
   min.loc = -1;

#pragma omp parallel
   {
     /*
     double reduce_time = 0;
     double update_time = 0;
     double sync_time = 0;
     */

     //double tic = omp_get_wtime();
     t_initialize(0, numVertices, dist, prev, inTree);
     //double toc = omp_get_wtime();
     //printf("Init, Thread: %d Time: %f \n", 
     //	    omp_get_thread_num(), toc-tic);


     //#pragma omp master //single may cause mem shift
     dist[source] = 0;
     
       
     //for not split over threads
     for(int j = 1; j < numVertices; ++j)
       {

	 int vert = -1;

	 //tic = omp_get_wtime();
	 #pragma omp single
	 {
	   //Get Min Vertex
	   min.dist = std::numeric_limits<double>::infinity();
	   min.loc = -1;
	 }
	 //toc = omp_get_wtime();
	 //sync_time += (toc-tic);

	 ///tic = omp_get_wtime();
#pragma omp for reduction(minimum:min) 
	 for(int i = 0; i < numVertices; ++i)
	   {
	     if(!inTree[i] && min.loc == -1)
	       {
		 min.dist = dist[i];
		 min.loc = i;
	       }
	     if(!inTree[i] && dist[i] < min.dist)
	       {
		 min.dist = dist[i];
		 min.loc = i;
	       }
	   }
	 vert = min.loc;
	 //toc = omp_get_wtime();
	 //	 reduce_time += (toc-tic);

	 //#pragma omp single
	 {
	   inTree[vert] = true;
	 }
	 
        //tic = omp_get_wtime();
#pragma omp for  
	 for(int i = 0; i < numVertices; ++i)
	   {

	     if(!inTree[i] && dist[i] > dist[vert] + adjMatrix[vert][i])
	       {
	
		 dist[i] = dist[vert] + adjMatrix[vert][i];
		 prev[i] = vert;

		 
	       }
	   }
	 //toc = omp_get_wtime();
	 //update_time += (toc-tic);
	 
       }

   /*
     printf("Reduce, Thread: %d Time: %f \n",
	    omp_get_thread_num(), reduce_time);
     printf("Update, Thread: %d Time: %f \n",
	    omp_get_thread_num(), update_time);
     printf("Sync, Thread: %d Time: %f \n",
	    omp_get_thread_num(), sync_time);
   */
   }
}
   

int getPath(int source, int dest, const int* prev, int*& path)
{
  std::vector<int> reversePath;
   int v = dest;
   while(v != source && v != -1)
   {
      reversePath.push_back(v);
      v = prev[v];
   }

   if(v == -1)
     {
       printf("No Path Exists\n");
     }
  

   path = new int[reversePath.size()+1];
   path[0] = source;
   for(unsigned i = 1; i <= reversePath.size(); i++)
   {
      path[i] = reversePath[reversePath.size() - i];
   }

   return reversePath.size()+1;
}
