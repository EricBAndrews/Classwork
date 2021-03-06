#include "upc.h"

#ifndef __CS267_COMMON_H__
#define __CS267_COMMON_H__

inline int min( int a, int b ) { return a < b ? a : b; }
inline int max( int a, int b ) { return a > b ? a : b; }

#define true 1
#define false 0

//
//  saving parameters
//
//const int NSTEPS = 1000;
//const int SAVEFREQ = 10;
#define NSTEPS 1000
#define SAVEFREQ 10

//
// particle data structure
//
typedef struct {
  double x;
  double y;
  double vx;
  double vy;
  double ax;
  double ay;
} particle_t;

//
//  timing routines
//
double read_timer();

//
//  simulation routines
//
void set_size(int n);
void init_particles(int n, shared particle_t *p);
void apply_force(shared particle_t* particle,
                 shared particle_t* neighbor,
                 double *dmin, double *davg, int *navg);
void move(shared particle_t *p );


//
//  I/O routines
//
FILE *open_save( char *filename, int n );
void save(FILE *f, int n, shared particle_t *p);

//
//  argument processing routines
//
int find_option( int argc, char **argv, const char *option );
int read_int( int argc, char **argv, const char *option, int default_value );
char *read_string( int argc, char **argv, const char *option, char *default_value );

// My Array
shared typedef struct {
  shared upc_lock_t* lock;
  shared int* data;
  int size;
  int n;
} array_t;

// global variables
shared particle_t* particles;
shared array_t* bins;

void array_t_init(shared array_t *a);
void array_t_get(shared array_t *a, int i, int* p);
//void array_t_get(shared array_t *a, int i, int* p);
//void array_t_push_back(shared array_t *a, shared particle_t* p);
void array_t_push_back(shared array_t *a, int pIndex);
void array_t_clear(shared array_t *a);
void array_t_size(shared array_t *a, int *size);

/*
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

*/
#endif
