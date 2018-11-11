/*
For your openacc code
*/

const char* dgemm_desc = "OpenACC blocked dgemm";

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format. 
 * On exit, A and B maintain their input values. */  
void square_dgemm (int lda, double* restrict A, double* restrict B, double* restrict C) {
#pragma acc parallel loop vector_length(64) num_gangs(1024) copyin(A[0:lda*lda]) copyin(B[0:lda*lda]) copy(C[0:lda*lda]) independent
  for (int i = 0; i < lda; ++i) {
    #pragma acc loop independent
    for (int j = 0; j < lda; ++j) {
      double cij = C[i + j*lda];
      for (int k = 0; k < lda; ++k) {
	cij += A[k*lda + i] * B[j*lda + k];
      }
      C[i + j*lda] = cij;
    }
  }
}
