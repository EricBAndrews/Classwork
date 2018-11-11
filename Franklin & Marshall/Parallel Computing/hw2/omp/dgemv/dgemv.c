#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

void omp_dgemv(int lda, double *A, double *x, double *y) {
  #pragma omp for
  for (int i = 0; i < lda; ++i) {
    for (int j = 0; j < lda; ++j) {
      y[i] += A[i,j] * x[i];
    }
  }
}

double *makeMatrix(int lda) {
// double *A = _mm_alloc will work too! And will coalesce if needed on some
// hardware
  double *A = (double *) aligned_alloc(32, lda*lda*sizeof(double));
  //double *A = (double *) malloc(lda*lda*sizeof(double));
  if(A == NULL) {
    printf("Error Alloc A\n");
  }

  for(int row = 0; row < lda; ++row) {
    for(int col = 0; col < lda; ++col) {
      A[row*lda+col] = row*lda+col * 1.00;
    }
  }
  return A;
}

double *makeVector(int lda, double value) {

  double *x = (double*) aligned_alloc(32, lda*sizeof(double));
  //double *x = (double *) malloc(lda*sizeof(double));
  if(x == NULL) {
    printf("Error alloc x\n");
  }
  for(int i = 0; i < lda; ++i) {
    x[i] = value;
  }

  return x;
}

int main(int argc, char* argv[]) {
  
  double *A = makeMatrix(N);
  double *x = makeVector(N, 1.000000001);
  double *y = makeVector(N, 0.0);

  //tic
  time_t start = time(NULL);
  omp_dgemv(N, A, x, y);
  time_t end = time(NULL);

  time_t elapsedTime = end - start;
  
  //What time is it
  printf("time elapsed: %i\n", (int)elapsedTime);

  free(A);
  free(x);
  free(y);
  return 0;
}
