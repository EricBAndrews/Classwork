/*
  Starting file for the cuda version.
  You do not have to do the same multple level block for this to work

*/

#include<stdio.h>

const char* dgemm_desc = "CUDA dgemm";

#if !defined(BLOCK_SIZE)
#define BLOCK_SIZE 10
#endif

#if !defined(CUDA_BLOCK_SIZE)
#define CUDA_BLOCK_SIZE 16
#endif

#define min(a,b) (((a)<(b))?(a):(b))

// Perform smaller dgemm operation using CUDA
__global__ void do_block(int lda, int i, int j, int k, double*matA, double* matB,
			 double* matC, int M, int N) {
  /* int row = i + threadIdx.x + (blockIdx.x * CUDA_BLOCK_SIZE); */
  /* int col = j + threadIdx.y + (blockIdx.y * CUDA_BLOCK_SIZE); */
  // row, col within block
  int locRow = threadIdx.x / BLOCK_SIZE;
  int locCol = threadIdx.x % BLOCK_SIZE;
  // row, col within full matrix
  int glbRow = i + locRow;
  int glbCol = j + locCol;
  //int lBound = min(BLOCK_SIZE, lda-glbRow);
  //if(threadIdx.x == 0) printf("lBound: %i\n", lBound);
  double a;
  double b;
  double cij;
  //if(threadIdx.x < BLOCK_SIZE * BLOCK_SIZE) {
  //if(glbRow < lda && glbCol < lda) {
  for (int l = 0; l < BLOCK_SIZE; ++l) {
    //if (locRow < M && locCol < N) {
    //printf("i: %i | j: %i | locRow: %i | locCol: %i | glbRow: %i | glbCol: %i | M: %i | N: %i\n", i, j, locRow, locCol, glbRow, glbCol, M, N);
    cij = 0;
    //for (int l = 0; l < lBound; ++l) {
    //printf("matB[%i][%i]: %f\n", l, glbCol, matB[l*lda + glbCol]);
    if ((i+l) < M && (j+l) < N) {
      if (glbRow == 0 && glbCol == 0) printf("M: %i | N: %i | glbRow+l: %i | glbCol+l: %i\n", M, N, glbRow+l, glbCol+l);
      a = matA[glbRow*lda + i+l];
      b = matB[(j+l)*lda + glbCol];
      cij += a * b;
      if (glbRow == 0 && glbCol == 0) printf("i: %i | j: %i | l: %i | cij: %f | matC[0][0]: %f\n", i, j, l, cij, matC[0]);
    }
    matC[glbRow*lda + glbCol] += cij;
    //if (glbRow == 0 && glbCol ==0 ) printf("matC: %.1f\n", matC[glbRow*lda + glbCol]);
  }
}

__global__ void printDeviceMatrix(double* mat, int lda) {
  for (int i = 0; i < lda; ++i) {
    for (int j = 0; j < lda; ++j) {
      if (mat[i*lda + j] > 0) printf(" ");
      printf("%.1f ", mat[i*lda + j]);
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
  /* for (int i = 0; i < lda; ++i) { */
  /*   for (int j = 0; j < lda; ++j) { */
  /*     if (A[i*lda + j] > 0) printf(" "); */
  /*     printf("%.1f ", A[i*lda + j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  //printDeviceMatrix<<<1, 1>>>(matA, lda);
  //printDeviceMatrix<<<1, 1>>>(matB, lda);
  //printDeviceMatrix<<<1, 1>>>(matC, lda);
  /* For each block-row of A */ 
  for (int i = 0; i < lda; i += BLOCK_SIZE) {
    /* For each block-column of B */
    for (int j = 0; j < lda; j += BLOCK_SIZE) {
      /* Accumulate block dgemms into block of C */
      for (int k = 0; k < lda; k += BLOCK_SIZE) {
	/* Correct block dimensions if block "goes off edge of" the matrix */
	int M = min(BLOCK_SIZE, lda-i);
	int N = min(BLOCK_SIZE, lda-j);
	// dimGrid = threads per block
	// dimBlock = block layout
	
	/* dim3 dimBlock(CUDA_BLOCK_SIZE, CUDA_BLOCK_SIZE); */

	/* int gridSize = BLOCK_SIZE / CUDA_BLOCK_SIZE; // 2 */
	/* if (gridSize * CUDA_BLOCK_SIZE < BLOCK_SIZE) { // 32 < 41 */
	/*   ++gridSize; */
	/* } */
	/* dim3 dimGrid(gridSize, gridSize); */
	

	/* Perform individual block dgemm */
	// printf("i: %i; j: %i; k: %i\n", i, j, k);
	do_block<<<1, 256>>>(lda, i, j, k, matA, matB, matC, M, N);
	// do_block(lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);
      }
    }
  }
  cudaDeviceSynchronize();
  cudaMemcpy(C, matC, matSize, cudaMemcpyDeviceToHost);
  //printDeviceMatrix<<<1, 1>>>(matC, lda);
  /* for (int i = 0; i < lda; ++i) { */
  /*   for (int j = 0; j < lda; ++j) { */
  /*     printf("%.1f ", C[i*lda + j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
}
