/*
  Starting file for the cuda version.
  You do not have to do the same multple level block for this to work

*/

#include<stdio.h>

const char* dgemm_desc = "CUDA dgemm";

#if !defined(BLOCK_SIZE)
#define BLOCK_SIZE 512
#endif

#if !defined(CUDA_BLOCK_SIZE)
#define CUDA_BLOCK_SIZE 16
#endif

#if !defined(CUDA_GRID_SIZE)
#define CUDA_GRID_SIZE 32
#endif

#define min(a,b) (((a)<(b))?(a):(b))

// Perform smaller dgemm operation using CUDA
__global__ void do_block(int lda, double*matA, double* matB, double* matC, int M, int N, int K) {
  int row = threadIdx.y + blockIdx.y*CUDA_BLOCK_SIZE;
  int col = threadIdx.x + blockIdx.x*CUDA_BLOCK_SIZE;;
  double c;
  //double a, b, c;
  //printf("blockIdx.x: %i | blockIdx.y: %i | gridDim.x: %i | gridDim.y: %i\n", blockIdx.x, blockIdx.y, gridDim.x, gridDim.y);
  if (row < M && col < N) {
    //printf("row: %i | col: %i\n", row, col);
    c = matC[row + col*lda];
    for (int k = 0; k < K; ++k) {
      //a = matA[k*lda + row];
      //b = matB[col*lda + k];
      //c += a * b;
      c += matA[k*lda + row] * matB[col*lda + k];
    }
    matC[row + col*lda] = c;
  }
}

__global__ void printDeviceMatrix(double* mat, int lda) {
  for (int i = 0; i < lda; ++i) {
    for (int j = 0; j < lda; ++j) {
      if (mat[i*lda + j] > 0) printf(" ");
      printf("%.0f ", mat[i*lda + j]);
    }
    printf("\n");
  }
}
/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format. 
 * On exit, A and B maintain their input values. */  
void square_dgemm (int lda, double* A, double* B, double* C) {
  // transfer the matrices over, allocate size for C
  size_t matSize = lda * lda * sizeof(double);
  double* matA;
  double* matB;
  double* matC;
  cudaMalloc(&matA, matSize);
  cudaMalloc(&matB, matSize);
  cudaMalloc(&matC, matSize);
  cudaMemcpy(matA, A, matSize, cudaMemcpyHostToDevice);
  cudaMemcpy(matB, B, matSize, cudaMemcpyHostToDevice);
  /* For each block-row of A */ 
  for (int i = 0; i < lda; i += BLOCK_SIZE) {
    /* For each block-column of B */
    for (int j = 0; j < lda; j += BLOCK_SIZE) {
      /* Accumulate block dgemms into block of C */
      for (int k = 0; k < lda; k += BLOCK_SIZE) {
	/* Correct block dimensions if block "goes off edge of" the matrix */
	int M = min(BLOCK_SIZE, lda-i);
	int N = min(BLOCK_SIZE, lda-j);
	int K = min(BLOCK_SIZE, lda-k);

	//int gridSize = BLOCK_SIZE / CUDA_BLOCK_SIZE;

	//dim3 gridDim(gridSize, gridSize);
	dim3 gridDim(CUDA_GRID_SIZE, CUDA_GRID_SIZE);
	dim3 blockDim(CUDA_BLOCK_SIZE, CUDA_BLOCK_SIZE);

	/* Perform individual block dgemm */
	// printf("i: %i; j: %i; k: %i\n", i, j, k);
	do_block<<<gridDim, blockDim>>>(lda, matA + k*lda + i, matB + j*lda + k, matC + i + j*lda, M, N, K);
      }
    }
  }
  cudaDeviceSynchronize();
  cudaMemcpy(C, matC, matSize, cudaMemcpyDeviceToHost);
  //printDeviceMatrix<<<1, 1>>>(matC, lda);
  /* for (int i = 0; i < lda; ++i) { */
  /*   for (int j = 0; j < lda; ++j) { */
  /*     printf("%.2f ", C[i*lda + j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
}
