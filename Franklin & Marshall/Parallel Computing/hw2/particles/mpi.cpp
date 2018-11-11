#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <mpi.h>
#include "common.h"
using namespace std;

//
//  tuned constants
//
#define density 0.0005
#define mass    0.01
#define cutoff  0.01
#define min_r   (cutoff/100)
#define dt      0.0005

// calculate particle's bin number
int binNum(particle_t &p, int bpr) {
  return (floor(p.x/cutoff) + bpr*floor(p.y/cutoff));
}

int procNum(int binNum, int bpr, int procHeight) {
  return (binNum % bpr) / procHeight;
}

//
//  benchmarking program
//
int main(int argc, char **argv) {
  int navg, nabsavg = 0;
  double dmin, davg, absmin = 1.0, absavg = 0.0;
  double rdavg, rdmin;
  int rnavg;

  if (find_option(argc, argv, "-h") >= 0) {
    printf( "Options:\n" );
    printf( "-h to see this help\n" );
    printf( "-n <int> to set the number of particles\n" );
    printf( "-o <filename> to specify the output file name\n" );
    printf( "-s <filename> to specify a summary file name\n" );
    printf( "-no turns off all correctness checks and particle output\n");
    return 0;
  }
    
  int n = read_int(argc, argv, "-n", 1000);

  char *savename = read_string(argc, argv, "-o", NULL);
  char *sumname = read_string(argc, argv, "-s", NULL);

  // set up mpi
  int n_proc, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  FILE *fsave = savename && rank == 0 ? fopen(savename, "w") : NULL;
  FILE *fsum = sumname && rank == 0 ? fopen (sumname, "a") : NULL;

  // create particle datatype
  MPI_Datatype PARTICLE;
  MPI_Type_contiguous(6, MPI_DOUBLE, &PARTICLE);
  MPI_Type_commit(&PARTICLE);
    
  // create spatial bins (of size cutoff by cutoff)
  // each process has just the bins for its own particles plus the neighbor above and below.
  double size = sqrt(density * n);
  int bpr = ceil(size / cutoff);
  int numbins = bpr * bpr;
  int rpp = bpr / n_proc; // rows per process
  if (rpp * n_proc < bpr) {
    ++rpp;
  }
  rpp += 2;
  int binsPerProc = bpr * rpp;
  //printf("there are %i bins; each process gets %i\n", numbins, binsPerProc);
  // printf("there are %i bins per row; each process has %i rows\n", bpr, rpp);
  vector<particle_t*> *bins = new vector<particle_t*>[binsPerProc];
  
  // initialize particles
  int numMyParticles;
  particle_t *myParticles;
  int procHeight = bpr / n_proc;
  if (procHeight * n_proc < bpr) {
    ++procHeight;
  }
  // printf("my rank is %i\n", rank);
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    // printf("initializing particles\n");
    particle_t *particles = (particle_t*) malloc(n * sizeof(particle_t));
    // printf("there are %i particles\n", n);
    set_size(n);
    init_particles(n, particles);
    // put particles into vectors to send
    vector<particle_t*> *processVecs = new vector<particle_t*>[n_proc];
    for (int i = 0; i < n; ++i) {
      int curProcNum = procNum(binNum(particles[i], bpr), bpr, procHeight);
      processVecs[curProcNum].push_back(&particles[i]);
    }
    // send vectors to processes
    for (int i = 1; i < n_proc; ++i) {
      int sizeToSend = processVecs[i].size();
      MPI_Send(&sizeToSend, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&processVecs[i][0], processVecs[i].size(), PARTICLE, i, 1,
               MPI_COMM_WORLD);
    }
    // handle own particles
    numMyParticles = processVecs[0].size();
    myParticles = (particle_t*) malloc(numMyParticles * sizeof(particle_t));
    myParticles = processVecs[0][0];
  }

  // recieve vectors
  if (rank > 0) {
    MPI_Recv(&numMyParticles, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    myParticles = (particle_t*) malloc(numMyParticles *
                                                   sizeof(particle_t));
    MPI_Recv(&myParticles[0], numMyParticles, PARTICLE, 0, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }

  //
  //  simulate a number of time steps
  //
  MPI_Barrier(MPI_COMM_WORLD); // make sure everybody has their particles
  // printf("i'm proc %i, and i have %i particles\n", rank, numMyParticles);
  double simulation_time = read_timer();
  for (int step = 0; step < NSTEPS; step++) {
    // printf("i'm proc %i on step %i\n", rank, step);
    navg = 0;
    davg = 0.0;
    dmin = 1.0;

    // clear bins at each time step
    for (int m = 0; m < binsPerProc; m++) {
      bins[m].clear();
    }

    // printf("cleared bins from proc %i\n", rank);
    
    // place particles in bins
    for (int i = 0; i < numMyParticles; ++i) {
      int curBinNum = binNum(myParticles[i], bpr); // get global bin number
      curBinNum %= bpr;
      curBinNum += bpr; // get local bin number
      bins[curBinNum].push_back(myParticles + i);
      // printf("pushing to bin %i\n", curBinNum);
      // printf("bin %i has size %i\n", curBinNum, (int)bins[curBinNum].size());
      if (i % 100 == 0) {
        // printf("proc %i pushed %i particles\n", rank, i);
      }
      // bins[binNum(particles[i],bpr)].push_back(particles + i);
    }

    // printf("proc %i has put particles in bins successfully\n", rank);
    MPI_Barrier(MPI_COMM_WORLD);
    // communicate borders
    if (n_proc > 1) { // if only 1 process, no need to send anything
      // send bottom bins down, recieve into top bins
      for (int i = 0; i < bpr; ++i) {
        int outBin = ((rpp - 1) * bpr) + i; // local bin to send
        int inBin = i; // local bin to recieve into
        int outSize = bins[outBin].size();
        int inSize;
        // communicate sizes
        if (rank == 0) { // don't need to recieve, only need to send
          MPI_Send(&outSize, 1, MPI_INT, rank+1, 2, MPI_COMM_WORLD);
        }
        else if (rank == n_proc - 1) { // only need to recieve
          MPI_Recv(&inSize, 1, MPI_INT, rank-1, 2, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
        }
        else {
          MPI_Sendrecv(&outSize, 1, MPI_INT, rank+1, 2, // send size down
                       &inSize, 1, MPI_INT, rank-1, 2, // recieve from up
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        // send info
        if (rank == 0) {
          MPI_Send(&bins[outBin][0], outSize, PARTICLE, rank+1, 3, MPI_COMM_WORLD);
        }
        else if (rank == n_proc - 1) {
          bins[inBin].resize(inSize);
          MPI_Recv(&bins[inBin][0], inSize, PARTICLE, rank-1, 3, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
        }
        else {
          bins[inBin].resize(inSize);
          MPI_Sendrecv(&bins[outBin][0], outSize, PARTICLE, rank+1, 3,
                       &bins[inBin][0], inSize, PARTICLE, rank-1, 3,
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
      }

      // printf("proc %i, done sending down!\n", rank);

      // send top bins up, recieve into bottom bins
      for (int i = 0; i < bpr; ++i) {
        int outBin = bpr + i; // bin to send
        int inBin = (bpr * (rpp - 1)) + i; // bin to recieve into
        int outSize = bins[outBin].size();
        printf("proc %i, outSize: %i\n", rank, outSize);
        int inSize;
        // communicate sizes
        if (rank == 0) { // only need to recieve
          MPI_Recv(&inSize, 1, MPI_INT, rank+1, 2, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
          printf("proc %i, inSize %i\n", rank, inSize);
        }
        else if (rank == n_proc - 1) { // only need to send
          MPI_Send(&outSize, 1, MPI_INT, rank-1, 2, MPI_COMM_WORLD);
        }
        else {
          MPI_Sendrecv(&outSize, 1, MPI_INT, rank-1, 2, // send size down
                       &inSize, 1, MPI_INT, rank+1, 2, // recieve from up
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("proc %i, done communicating sizes!\n", rank);
        
        // send info
        if (rank == 0) {
          printf("proc %i, ready to recieve\n", rank);
          bins[inBin].resize(inSize);
          MPI_Recv(&bins[inBin][0], inSize, PARTICLE, rank+1, 3, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
        }
        else if (rank == n_proc - 1) {
          printf("proc %i, ready to send\n", rank);
          // THIS SEGFAULTS
          MPI_Send(&bins[outBin][0], outSize, PARTICLE, rank-1, 3, MPI_COMM_WORLD);
          printf("proc %i, sending %i particles", rank, outSize);
        }
        else {
          bins[inBin].resize(inSize);
          MPI_Sendrecv(&bins[outBin][0], outSize, PARTICLE, rank-1, 3,
                       &bins[inBin][0], inSize, PARTICLE, rank+1, 3,
                       MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        printf("proc %i, communicated bin %i/71\n", rank, i);
      }
      printf("proc %i, done sending up!\n", rank);
    }
    // printf("done communicating\n");
    //
    //  compute forces
    //
    for (int p = 0; p < numMyParticles; ++p) {
      myParticles[p].ax = myParticles[p].ay = 0;
        
      // find current particle's bin, handle boundaries
      int cbin = binNum(myParticles[p], bpr);
      int lowi = -1, highi = 1, lowj = -1, highj = 1;
      if (cbin < bpr) {
        lowj = 0;
      }
      if (cbin % bpr == 0) {
        lowi = 0;
      }
      if (cbin % bpr == (bpr-1)) {
        highi = 0;
      }
      if (cbin >= bpr*(bpr-1)) {
        highj = 0;
      }

      // apply nearby forces
      for (int i = lowi; i <= highi; ++i) {
        for (int j = lowj; j <= highj; ++j) {
          cbin %= bpr;
          cbin += bpr; // turn cbin (global) into a local bin number
          int nbin = cbin + i + bpr*j;
          for (int k = 0; k < bins[nbin].size(); ++k) {
            apply_force(myParticles[p], *bins[nbin][k], &dmin, &davg, &navg);
          }
        }
      }
    }
        
    //
    //  move particles
    //
    MPI_Barrier(MPI_COMM_WORLD);
    for (int p = 0; p < numMyParticles; ++p) {
      move(myParticles[p]);
    }

    if (find_option(argc, argv, "-no") == -1) {
      //  computing statistical data

      MPI_Reduce(&davg, &rdavg, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
      MPI_Reduce(&navg, &rnavg, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
      MPI_Reduce(&dmin, &rdmin, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

      if (rank == 0) {
        if (rnavg) {
          absavg += rdavg / rnavg;
          nabsavg++;
        }
        if (rdmin < absmin) absmin = rdmin;
      }
      //
      //  save if necessary
      //
      if (fsave && (step%SAVEFREQ) == 0)
        save(fsave, n, myParticles);
    }
  }
  simulation_time = read_timer() - simulation_time;

  if (rank == 0) {
    printf("n = %d, simulation time = %g seconds", n, simulation_time);

    if (find_option( argc, argv, "-no" ) == -1) {
      if (nabsavg) absavg /= nabsavg;
      // 
      //  -the minimum distance absmin between 2 particles during the run of the simulation
      //  -A Correct simulation will have particles stay at greater than 0.4 (of cutoff) with typical values between .7-.8
      //  -A simulation were particles don't interact correctly will be less than 0.4 (of cutoff) with typical values between .01-.05
      //
      //  -The average distance absavg is ~.95 when most particles are interacting correctly and ~.66 when no particles are interacting
      //
      printf( ", absmin = %lf, absavg = %lf", absmin, absavg);
      if (absmin < 0.4) printf ("\nThe minimum distance is below 0.4 meaning that some particle is not interacting");
      if (absavg < 0.8) printf ("\nThe average distance is below 0.8 meaning that most particles are not interacting");
    }
    printf("\n");

    //
    // Printing summary data
    //
    if( fsum)
      fprintf(fsum,"%d %g\n",n,simulation_time);
  }
  
  //
  // Clearing space
  //
  if( fsum )
    fclose( fsum );
  free( myParticles );
  delete [] bins;
  if( fsave )
    fclose( fsave );

  MPI_Finalize();
  
  return 0;
}
