
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/* ---------------------------------------------------------------------
 * alloc_matrix()
 * ------------------------------------------------------------------ */


double**                  alloc_matrix

  ( int                     m,
    int                     n )

{
  double**  rows = NULL;
  double*   data = NULL;

  int       i;


  assert ( (m >= 0) && (n >= 0) );

  if ( (m == 0) || (n == 0) )
  {
    return rows;
  }

  rows = (double**) malloc ( m *     sizeof(double*) );
  data = (double*) malloc ( m * n * sizeof(double) );

  if ( ! rows || ! data )
  {
    fprintf ( stderr, "Out of memory.\n" );
    exit    ( 1 );
  }

  for ( i = 0; i < m; i++ )
  {
    rows[i] = &data[i * n];
  }

  return rows;
}


/* ---------------------------------------------------------------------
 * free_matrix()
 * ------------------------------------------------------------------ */


void                      free_matrix

  ( double**                mat )

{
  if ( mat )
  {
    free ( mat[0] );
    free ( mat );
  }
}


/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */


int                       main

  ( int                     argc,
    char**                  argv )

{
  const int  N = 1000;

  double**   a = alloc_matrix ( N, N );
  double     c[N];
  double     t;
  int        i, j, k;


  printf ( "Initializing the matrix ...\n" );

  for ( j = 0; j < N; j++ )
  {
    for ( i = 0; i < N; i++ )
    {
      a[i][j] = (double) abs ( i - j );
    }
  }

  printf ( "Executing the Gram-Schmidt algorithm ...\n" );

  for ( j = 0; j < N; j++ )
  {
    for ( k = 0; k < j; k++ )
    {
      c[k] = 0.0;

      for ( i = 0; i < N; i++ )
      {
        c[k] += a[i][k] * a[i][j];
      }
    }

    for ( k = 0; k < j; k++ )
    {
      for ( i = 0; i < N; i++ )
      {
        a[i][j] -= c[k] * a[i][k];
      }
    }

    t = 0.0;

    for ( i = 0; i < N; i++ )
    {
      t += a[i][j] * a[i][j];
    }

    t = sqrt ( t );

    if ( t <= 0.0 )
    {
      fprintf ( stderr, "Singular matrix.\n" );
      return  1;
    }

    t = 1.0 / t;

    for ( i = 0; i < N; i++ )
    {
      a[i][j] *= t;
    }
  }

  printf ( "Done.\n" );

  return 0;
}

