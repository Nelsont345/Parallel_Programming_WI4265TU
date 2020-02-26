
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

/* ---------------------------------------------------------------------
 * constants
 * ------------------------------------------------------------------ */

#define                   NRANDOM     10000000
#define                   NSAMPLES    100
#define                   NTHREADS    4

/* ---------------------------------------------------------------------
 * calc_random()
 *
 *   Returns a pseudo random number.
 * ------------------------------------------------------------------ */

int                     calc_random ()
{
  /* Implement this ... */
  return 0;
}

/* ---------------------------------------------------------------------
 * thread_func()
 *
 *   The thread entry point. This function generates a sequence of
 *   pseudo random numbers.
 * ------------------------------------------------------------------ */

void*                     thread_func

  ( void*                   arg )

{
  int  i;

  for ( i = 0; i < NRANDOM; i++ )
  {
    int  num = calc_random ();

    /* Store a few samples for verification ... */
  }

  return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

  ( int                     argc,
    char**                  argv )

{
  pthread_t  threads[NTHREADS];

  /* Create the threads ... */

  /* Join the threads ... */

  /* Verify that all threads have generated the same sequence
   * of pseudo random numbers ... */

  return 0;
}

