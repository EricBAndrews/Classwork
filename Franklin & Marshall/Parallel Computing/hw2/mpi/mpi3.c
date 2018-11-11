/* This program demos sendrecv that will help to prevent deadlocks
 * It does the same random add as mpi2
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
  int my_rank;
  int nproc;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int r = rand()%10;
  printf("Rank: %d My number: %d \n", my_rank, r);

  int other;

  /*
   *int MPI_Sendrecv(void* sbuffer, int scount, MPI_Datatype stype, int dest, int stag,
   * void* rbuff, int rcount, MPI_Datatype, int source, int rtag, 
   * MPI_COMM, MPI_STATUS);
   */
  MPI_Status status;

  MPI_Sendrecv((void*) &r, 1, MPI_INT, (my_rank+1)%nproc, 1, 
	       (void*) &other, 1, MPI_INT, (my_rank-1+nproc)%nproc, 1,
	       MPI_COMM_WORLD, &status);

  r += other;

  printf("Rank: %d sum: %d \n", my_rank, r);
  

  MPI_Finalize();
  return 0;

}
