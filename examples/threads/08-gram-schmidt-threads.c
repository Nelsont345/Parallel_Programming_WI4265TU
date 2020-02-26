
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

/* ---------------------------------------------------------------------
 * types and constants
 * ------------------------------------------------------------------ */

#define                   NTHREADS  5

struct                    reduction
{
  /* Copy from the previous exercise ... */
};

struct                    data
{
  /* Continue here ... */
};

typedef struct reduction  reduction_t;
typedef struct data       data_t;

/* ---------------------------------------------------------------------
 * reduction_init()
 *
 *   Initialises a reduction variable. The parameter "nt" specifies
 *   the number of threads that will participate in a reduction
 *   operation.
 * ------------------------------------------------------------------ */

void                      reduction_init

  ( reduction_t*            red,
    int                     nt )

{
  assert ( red && (nt > 0) );

  /* Copy from the previous exercise ... */
}

/* ---------------------------------------------------------------------
 * reduction_destroy()
 *
 *   Destroys a reduction variable.
 * ------------------------------------------------------------------ */

void                      reduction_destroy

  ( reduction_t*            red )

{
  assert ( red );

  /* Copy from the previous exercise ... */
}

/* ---------------------------------------------------------------------
 * reduction_sum()
 *
 *   Calculates a global sum across multiple threads. The number
 *   of threads calling this function must be equal to the
 *   parameter "nt" specified in the call to the reduction_init()
 *   function.
 * ------------------------------------------------------------------ */

double                    reduction_sum

  ( reduction_t*            red,
    double                  val )

{
  assert ( red );

  double  result = 0.0;

  /* Copy from the previous exercise ... */

  return result;
}

/* ---------------------------------------------------------------------
 * matrix_alloc()
 *
 *   Allocates an m * n matrix. The matrix must be deallocated by
 *   calling the function matrix_free()
 * ------------------------------------------------------------------ */

double**                  matrix_alloc

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
 * matrix_free()
 *
 *   Deallocates a matrix that has been allocated by the function
 *   matrix_alloc().
 * ------------------------------------------------------------------ */

void                      matrix_free

  ( double**                mat )

{
  if ( mat )
  {
    free ( mat[0] );
    free ( mat );
  }
}

/* ---------------------------------------------------------------------
 * thread_func()
 *
 *   The thread entry point. This executes the Gram-Schmidt
 *   algorithm in parallel.
 * ------------------------------------------------------------------ */

void*                     thread_func

  ( void*                   arg )

{
  /* Continue here ... */

  return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

( int                     argc,
  char**                  argv )

{
  const int    msize  = 200;
  double**     matrix = matrix_alloc ( msize, msize );

  double       t;
  int          i, j;


  printf ( "Initialising the matrix ...\n" );

  for ( j = 0; j < msize; j++ )
  {
    for ( i = 0; i < msize; i++ )
    {
      matrix[i][j] = (double) abs ( i - j );
    }
  }

  printf ( "Executing the Gram-Schmidt algorithm ...\n" );

  /* Continue here: spawn threads and join them again ... */

  printf ( "Done.\n" );

  /* Check whether the first and last columns are
   * indeed orthogonal. */

  t = 0.0;

  for ( i = 0; i < msize; i++ )
  {
    t += matrix[i][0] * matrix[i][msize - 1];
  }

  if ( t < 1.0e-10 )
  {
    printf ( "Check (%g) passed.\n", t );
  }
  else
  {
    printf ( "Check (%g) FAILED.\n", t );
  }

  matrix_free ( matrix );

  return 0;
}
