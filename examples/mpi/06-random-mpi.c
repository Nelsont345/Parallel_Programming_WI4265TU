
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
    int  my_rank;
    int  flag;

    MPI_Initialized ( &flag );

    if ( flag )
    {
      MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

      srand ( (unsigned int) my_rank );
    }

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
  const double  eps = 1.0e-7;
  const int     N   = 10;
  int           k   = 0;

  double        numbers[N];
  double        start;
  int           iiter;


  MPI_Init ( &argc, &argv );

  printf   ( "Generating random numbers ...\n" );

  start = MPI_Wtime ();

  for ( iiter = 0; k < N; iiter++ )
  {
    double  v = next_random ();

    if ( v < eps )
    {
      numbers[k++] = v;
    }
  }

  printf ( "Ready in %d iterations (%g seconds).\n",
           iiter, (MPI_Wtime() - start) );
  printf ( "Numbers found:\n\n" );

  for ( k = 0; k < N; k++ )
  {
    printf ( "  %g\n", numbers[k] );
  }

  printf ( "\n" );

  MPI_Finalize ();

  return 0;
}

