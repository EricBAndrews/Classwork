/*
 * A Simple Send and Recv in MPI (Designed for 2 Processes)
 *
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  /* There are many MPI Data Types (here are some)
   * MPI_CHAR  --- signed char
   * MPI_SHORT --- signed short int
   * MPI_INT --- signed int
   * MPI_LONG --- signed long int
   * MPI_UNSIGNED --- unsigned int
   * MPI_DOUBLE --- double
   */

  //We are going to add two rand number to each other
  int r = rand()%10;
  //Why do they have the same random number ??? 
  //The rand algorith starts at the same rand seed for every process
  printf("Rank: %d My number: %d \n", my_rank, r);

  int other;
  //Because we do not a deadlock
  if(my_rank == 0) {
    //int MPI_Send (void *buf, int count, MPI_Datatype, int dest, int tag,
    // MPI_COM)
    MPI_Send((void*) &r, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
    //int MPI_Recv (void *buf, int count, MPI_Datatype, int source, int tag,
    // MPI_COM, MPI_STATUS)
    MPI_Recv((void*) &other, 1, MPI_INT, 1, 2, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
      
  }
  else if(my_rank == 1) {
      
    MPI_Recv((void*) &other, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    //I can break it fast, by changing the 0 to 1
    MPI_Send((void*) &r, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);

  }

  r = r + other;
  printf("Rank: %d sum: %d \n", my_rank, r);

  MPI_Finalize();

  return 0;
}
