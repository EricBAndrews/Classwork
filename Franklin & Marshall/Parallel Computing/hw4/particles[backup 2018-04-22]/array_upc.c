#include <stdio.h>
#include <stdlib.h>
#include "common_upc.h"
#include "upc.h"


void array_t_init(shared array_t *a) {
  a->lock = upc_global_lock_alloc();
  /* a->size = upc_global_alloc(sizeof(int), 1); */
  /* a->n = upc_global_alloc(sizeof(int), 1); */
  /* *(a->size) = 16; */
  /* *(a->n) = 0; */
  a->size = 16;
  a->n = 0;
  a->data = upc_global_alloc(sizeof(particle_t*), a->size);
}

//void array_t_get(shared array_t *a, int i, shared particle_t** p) {
void array_t_get(shared array_t* a, int i, int* p) {
  *p = a->data[i];
  //p = a->data[i];
}

//void array_t_push_back(shared array_t *a, shared particle_t *p) {
void array_t_push_back(shared array_t *a, int pIndex) {
  // printf("pushing back\n");
  // printf("a->size: %i\n", a->size);
  upc_lock(a->lock);
  if(a->n >= a->size) {
    int new_size = a->size * 2;
    //printf("hi\n");
    int* temp = malloc(sizeof(particle_t) * new_size);
    int i = 0; 
    for (i = 0 ; i < a->size; ++i) {
      temp[i] = a->data[i];
    }
    a->size = new_size;
    upc_free(a->data);
  }
  //a->data[a->n] = &particles[pIndex];
  a->data[a->n] = pIndex;
  a->n = a->n+1;
  upc_unlock(a->lock);
  // printf("pushed back\n");
}

void array_t_clear(shared array_t *a) {
  upc_lock(a->lock);
  a->n = 0;
  upc_unlock(a->lock);
}

void array_t_size(shared array_t *a, int *size) {
  *size = a->n;
}
