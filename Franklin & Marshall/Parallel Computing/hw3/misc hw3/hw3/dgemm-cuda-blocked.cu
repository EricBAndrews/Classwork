/*
Starting file for the cuda version.
You do not have to do the same multple level block for this to work

*/

const char* dgemm_desc = "CUDA dgemm";


/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format. 
 * On exit, A and B maintain their input values. */  
void square_dgemm (int lda, double* A, double * B, double* C)
{
	//fill me
}
