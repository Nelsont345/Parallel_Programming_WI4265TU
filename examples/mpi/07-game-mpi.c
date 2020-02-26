
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/* ---------------------------------------------------------------------
 * next_random()
 *
 * Returns a uniform random number in the range [0,1].
 * ------------------------------------------------------------------ */


double                    next_random

  ( void )

{
  static int  initialized = 0;
  int         next;

  if ( ! initialized )
  {
    unsigned int  seed = (unsigned int) time ( NULL );
    int           my_rank;
    int           flag;

    MPI_Initialized ( &flag );

    if ( flag )
    {
      MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

      seed += (unsigned int) (my_rank * 347);
    }

    srand ( seed );

    initialized = 1;
  }

  next = rand ();

  return ((double) next / (double) RAND_MAX);
}


/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */


int                       main

  ( int                     argc,
    char**                  argv )

{
  const int  N = 100;

  int        proc_count;


  MPI_Init      ( &argc, &argv );
  MPI_Comm_size ( MPI_COMM_WORLD, &proc_count );

  if ( proc_count < 2 )
  {
    fprintf ( stderr, "At least two processes are required.\n" );
    return 1;
  }

  /* Continue here ... */

  MPI_Finalize ();

  return 0;
}

