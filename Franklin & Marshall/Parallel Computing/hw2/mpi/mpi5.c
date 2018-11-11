/*Global communication bcast and reduce
 *Note other globals:
 * int MPI_Barrier(MPI_Comm comm)
 * int MPI_Bcast(void* buf, int count, MPI_Datatype, int source, MPI_COMM)
 * int MPI_Reduce(void* sbuf, void* rbuf, int count, MPI_Datatype, MPI_op, int target, MPI_COMM)
 * (Prefix Scan) int MPI_Scan(void *sbuf, void *rbuf, int count, MPI_Datatype, MPI_Op, MPI_Comm)
 * int MPI_Gather(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, int target, MPI_Comm)
 * int MPI_Scatter(void *sbuf, int scount, MPI_Datatype stype, void *rbuf, int rcount, MPI_Datatype rtype, source, MPI_COMM)
 * int MPI_Scatterv(void *sbuf, int *scount, int *displs, MPI_Datatype stype, void *rbuff, int rcount, MPI_Datatype rtype, int source, MPI_Comm)
 * int MPI_Alltoall(void *sbuff, int scount, MPI_Datatype stype, void* rbuf, int rcount, MPI_Datatype rtype, MPI_Comm)
 * int MPI_Alltoallv ....
 *-----Wow that is a lot and not even all of them!
 */

/* Some important MPI_Ops
 * MPI_MAX
 * MPI_MIN
 * MPI_SUM
 * MPI_PROD
 * There are a lot more too!
 */

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int done = 0, n, myid, numprocs, i;
  double PI25DT = 3.141592653589793238462643;
  double mypi, pi, h, sum, x;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  n = atoi(argv[1]);
  

    {

      MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
      h   = 1.0 / (double) n;
      sum = 0.0;
      for (i = myid + 1; i <= n; i += numprocs) {
	x = h * ((double)i - 0.5);
	sum += 4.0 / (1.0 + x*x);
      }
      mypi = h * sum;
    
      MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		 MPI_COMM_WORLD);
    
      if (myid == 0)
	printf("pi is approximately %.16f, Error is %.16f\n",
	       pi, fabs(pi - PI25DT));
    }
  MPI_Finalize();
  return 0;
}
