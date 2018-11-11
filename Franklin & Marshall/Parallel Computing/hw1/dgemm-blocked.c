/* 
    Please include compiler name below (you may also include any other modules you would like to be loaded)

COMPILER= gnu

    Please include All compiler flags and libraries as you want them run. You can simply copy this over from the Makefile's first few lines
 
CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm

*/

#include<stdio.h>

const char* dgemm_desc = "Simple blocked dgemm.";

#if !defined(BLOCK_SIZE)
#define BLOCK_SIZE 4
#endif

#include<immintrin.h>

#define min(a,b) (((a)<(b))?(a):(b))

/* This auxiliary subroutine performs a smaller dgemm operation
 *  C := C + A * B
 * where C is M-by-N, A is M-by-K, and B is K-by-N. */
void do_block_four (int lda, int M, int N, int K, double* A, double* B, double* C) {
  // grab 4x4 C block
  __m256d c0 = _mm256_loadu_pd(C + 0*lda);
  __m256d c1 = _mm256_loadu_pd(C + 1*lda);
  __m256d c2 = _mm256_loadu_pd(C + 2*lda);
  __m256d c3 = _mm256_loadu_pd(C + 3*lda);
  __m256d a, b0, b1, b2, b3;
  for (int i = 0; i < 4; ++i) {
    a = _mm256_loadu_pd(A + i*lda);
    b0 = _mm256_set1_pd(B[i + 0*lda]);
    b1 = _mm256_set1_pd(B[i + 1*lda]);
    b2 = _mm256_set1_pd(B[i + 2*lda]);
    b3 = _mm256_set1_pd(B[i + 3*lda]);
    c0 = _mm256_add_pd(c0, _mm256_mul_pd(a, b0));
    c1 = _mm256_add_pd(c1, _mm256_mul_pd(a, b1));
    c2 = _mm256_add_pd(c2, _mm256_mul_pd(a, b2));
    c3 = _mm256_add_pd(c3, _mm256_mul_pd(a, b3));
  }
  _mm256_storeu_pd(C + 0*lda, c0);
  _mm256_storeu_pd(C + 1*lda, c1);
  _mm256_storeu_pd(C + 2*lda, c2);
  _mm256_storeu_pd(C + 3*lda, c3);
}

void do_block (int lda, int M, int N, int K, double* A, double* B, double* C) {
  /* for each row i of A */
  for (int i = 0; i < M; ++i) {
    /* For each column j of B */
    for (int j = 0; j < N; ++j) {
      /* Compute C(i,j) */
      double cij = C[i+j*lda];
      for (int k = 0; k < K; ++k)
  	cij += A[i+k*lda] * B[k+j*lda];
      C[i+j*lda] = cij;
    }
  }
}


/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format. 
 * On exit, A and B maintain their input values. */  
void square_dgemm (int lda, double* A, double* B, double* C) {
  /* For each block-row of A */ 
  for (int i = 0; i < lda; i += BLOCK_SIZE) {
    /* For each block-column of B */
    for (int j = 0; j < lda; j += BLOCK_SIZE) {
      /* Accumulate block dgemms into block of C */
      for (int k = 0; k < lda; k += BLOCK_SIZE) {
	/* Correct block dimensions if block "goes off edge of" the matrix */
	// if (BLOCK_SIZE > i && BLOCK_SIZE > j && BLOCK_SIZE > k) {
	if (BLOCK_SIZE <= lda-i && BLOCK_SIZE <= lda-j && BLOCK_SIZE <= lda-k) {
	  do_block_four(lda, 4, 4, 4, A + i + k*lda, B + k + j*lda, C + i + j*lda);
	}
	else {
	  int M = min(BLOCK_SIZE, lda-i);
	  int N = min(BLOCK_SIZE, lda-j);
	  int K = min(BLOCK_SIZE, lda-k);

	  /* Perform individual block dgemm */
	  do_block(lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);
	}
      }
    }
  }
}
