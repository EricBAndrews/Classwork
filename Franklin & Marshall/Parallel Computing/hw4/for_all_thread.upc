#include <upc.h>
#include <stdio.h>


shared int a[2*THREADS];

int main() {
  
  int i;
  upc_forall(i = 0; i < 2*THREADS; ++i; &a[i]) {
      printf("Thread: %d i: %d %d \n", MYTHREAD, i, i + MYTHREAD);
      a[i] = i + MYTHREAD;
    }
   
   upc_barrier;

  for(i=0; i<2*THREADS; ++i) {
      printf("Thread: %d a[%d]= %d \n",
	     MYTHREAD, i, a[i]);
    }

}
