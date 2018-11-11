#include <stdio.h>
#include <stdlib.h>
#include "common.h"


void array_t_init(array_t *a)
{
  a->size = 16;
  a->n = 0;
  a->data = (particle_t **) malloc(sizeof(particle_t*)*a->size);
}

void array_t_get(array_t *a, int i, particle_t** p)
{
  *p = a->data[i]; 
}

void array_t_push_back(array_t *a, particle_t *p)
{
  if(a->n >= a->size)
    {
      int new_size = a->size * 2;
      particle_t **temp = malloc(sizeof(particle_t*)*new_size);
      int i = 0;
      for( i = 0 ; i < a->size; ++i)
	{
	  temp[i] = a->data[i];
	}
      a->size = new_size;;
      free(a->data);
    }
  a->data[a->n] = p;
  a->n = a->n+1;
}

void array_t_clear(array_t *a)
{
  a->n = 0;
}

void array_t_size(array_t *a, int *size)
{
  *size = a->n;
}
