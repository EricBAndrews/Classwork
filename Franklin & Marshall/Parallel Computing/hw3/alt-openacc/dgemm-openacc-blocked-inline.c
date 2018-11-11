/*
For your openacc code
*/

#if !defined(BLOCK_SIZE)
#define BLOCK_SIZE 16
#endif

#define min(a,b) (((a)<(b))?(a):(b))

const char* dgemm_desc = "OpenACC blocked dgemm";

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format. 
 * On exit, A and B maintain their input values. */  
void square_dgemm (int lda, double* A, double* B, double* C) {
  for (int i = 0; i < lda; i += BLOCK_SIZE) {
    for (int j = 0; j < lda; j += BLOCK_SIZE) {
      for (int k = 0; k < lda; k += BLOCK_SIZE) {
	// do each block
	int L = min(BLOCK_SIZE, lda-i);
	int M = min(BLOCK_SIZE, lda-j);
	int N = min(BLOCK_SIZE, lda-k);
	double c;
	for (int l = i; l < i+L; ++l) {
	  for (int m = j; m < j+M; ++m) {
	    //printf("l: %i | m: %i\n", l, m);
	    c = A[l + m*lda];
	    for (int n = k; n < k+N; ++n) {
	      c += A[l + n*lda] * B[n + m*lda];
	    }
	    C[l + m*lda] = c;
	  }
	}
      }
    }
  }
}
