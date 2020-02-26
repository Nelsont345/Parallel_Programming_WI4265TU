
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* ---------------------------------------------------------------------
 * types
 * ------------------------------------------------------------------ */

struct                    sparse_matrix
{
  int                       nrows;
  int                       ncols;
  int*                      offset;
  int*                      index;
  double*                   value;
};

typedef struct            sparse_matrix  sparse_matrix_t;

/* ---------------------------------------------------------------------
 * wtime()
 *
 *   Returns the wall-clock time in seconds since some moment in
 *   the past.
 * ------------------------------------------------------------------ */

double                    wtime

  ( void )

{
  static int             ini = 0;
  static struct timeval  tv0;

  struct timeval         tv;

  gettimeofday ( &tv, NULL );

  if ( ! ini )
  {
    tv0 = tv;
    ini = 1;
  }

  if ( tv0.tv_usec > tv.tv_usec )
  {
    tv.tv_usec  = 1000000 - (tv0.tv_usec - tv.tv_usec);
    tv.tv_sec  -= 1;
  }
  else
  {
    tv.tv_usec -= tv0.tv_usec;
  }

  return ((double) tv.tv_sec + 1.0e-6 * tv.tv_usec);
}


/* ---------------------------------------------------------------------
 * sparse_matrix_init()
 *
 *   Initialises a sparse matrix, given the number of rows, columns
 *   and non-zero values.
 * ------------------------------------------------------------------ */

void                      sparse_matrix_init

  ( sparse_matrix_t*        matrix,
    int                     nrows,
    int                     ncols,
    int                     nnz )

{
  assert ( nrows >= 0 );
  assert ( ncols >= 0 );
  assert ( nnz   >= 0 );

  memset ( matrix, 0x0, sizeof(*matrix) );

  matrix->nrows  = nrows;
  matrix->ncols  = ncols;
  matrix->offset = malloc ( (nrows + 1) * sizeof(*matrix->offset) );
  matrix->index  = malloc (  nnz        * sizeof(*matrix->index) );
  matrix->value  = malloc (  nnz        * sizeof(*matrix->value) );

  if ( (matrix->offset == NULL) ||
       (matrix->index  == NULL) ||
       (matrix->value  == NULL) )
  {
    fprintf ( stderr,
              "ERROR: failed to allocate a sparse matrix.\n" );
    exit    ( 1 );
  }

  memset ( matrix->offset, 0x0,
           (nrows + 1) * sizeof(*matrix->offset) );
}

/* ---------------------------------------------------------------------
 * sparse_matrix_destroy()
 *
 *   Destroys a sparse matrix.
 * ------------------------------------------------------------------ */

void                      sparse_matrix_destroy

  ( sparse_matrix_t*        matrix )

{
  free   ( matrix->offset );
  free   ( matrix->index );
  free   ( matrix->value );
  memset ( matrix, 0x0, sizeof(*matrix) );
}

/* ---------------------------------------------------------------------
 * sparse_matrix_read()
 *
 *   Reads a sparse matrix from a file in the Matrix Market
 *   coordinate format.
 * ------------------------------------------------------------------ */

void                      sparse_matrix_read

  ( sparse_matrix_t*        matrix,
    const char*             fname )

{
  FILE*   file = fopen ( fname, "r" );
  int     ierr = 0;

  int     nrows;
  int     ncols;
  int     nnz;
  int     irow;
  int     jcol;
  double  val;
  int     i, k, n;

  if ( ! file )
  {
    fprintf ( stderr, "ERROR: failed to open the file `%s\'.\n",
              fname );
    exit    ( 1 );
  }

  if ( fscanf( file, " %d %d %d", &nrows, &ncols, &nnz ) != 3 )
  {
    ierr = 1;
    goto error;
  }

  if ( (nrows < 0) || (ncols < 0) || (nnz < 0) )
  {
    ierr = 2;
    goto error;
  }

  sparse_matrix_init ( matrix, nrows, ncols, nnz );

  /* First pass: count the number of entries per row. */

  for ( i = 0; i < nnz; i++ )
  {
    if ( fscanf( file, " %d %d %le", &irow, &jcol, &val ) != 3 )
    {
      ierr = 3;
      goto error;
    }

    if ( (irow < 1) || (irow > nrows) ||
         (jcol < 1) || (jcol > ncols) )
    {
      ierr = 4;
      goto error;
    }

    matrix->offset[irow - 1]++;
  }

  fclose ( file );

  file = NULL;

  /* Prepare the offset array. */

  for ( irow = n = 0; irow <= nrows; irow++ )
  {
    k                    = matrix->offset[irow];
    matrix->offset[irow] = n;
    n                   += k;
  }

  if ( n != nnz )
  {
    ierr = 5;
    goto error;
  }

  /* Second pass: store the values in the sparse matrix. */

  file = fopen ( fname, "r" );

  if ( ! file )
  {
    fprintf ( stderr, "ERROR: failed to open the file `%s\'.\n",
              fname );
    exit    ( 1 );
  }

  if ( fscanf( file, " %d %d %d", &nrows, &ncols, &nnz ) != 3 )
  {
    ierr = 6;
    goto error;
  }

  if ( (nrows != matrix->nrows) ||
       (ncols != matrix->ncols) ||
       (nnz   != matrix->offset[nrows]) )
  {
    ierr = 7;
    goto error;
  }

  for ( i = 0; i < nnz; i++ )
  {
    if ( fscanf( file, " %d %d %le", &irow, &jcol, &val ) != 3 )
    {
      ierr = 8;
      goto error;
    }

    if ( (irow < 1) || (irow > nrows) ||
         (jcol < 1) || (jcol > ncols) )
    {
      ierr = 9;
      goto error;
    }

    k                = matrix->offset[irow - 1]++;
    matrix->index[k] = jcol - 1;
    matrix->value[k] = val;
  }

  fclose ( file );

  file = NULL;

  /* Correct the offset array. */

  for ( irow = n = 0; irow < nrows; irow++ )
  {
    k                    = matrix->offset[irow];
    matrix->offset[irow] = n;
    n                    = k;
  }

  if ( n != nnz )
  {
    ierr = 10;
    goto error;
  }

  /* No error occurred if this point is reached. */

  return;

error:

  fprintf ( stderr, "ERROR: failed to read the file `%s\' "
            "(ierr = %d).\n",
            fname, ierr );
  exit    ( 1 );
}

/* ---------------------------------------------------------------------
 * vector_init()
 *
 *   Fills a vector with random values.
 * ------------------------------------------------------------------ */

void                      vector_init

  ( double*                 vec,
    int                     len )

{
  int  i;

  for ( i = 0; i < len; i++ )
  {
    vec[i] = rand() / (double) RAND_MAX;
  }
}

/* ---------------------------------------------------------------------
 * matvec()
 *
 *   Executes a sparse matrix-vector product.
 * ------------------------------------------------------------------ */

void                      matvec

  ( double*                 lhs,
    const sparse_matrix_t*  mat,
    const double*           rhs )

{
  const int  nrows = mat->nrows;

  double     sum;
  int        irow;
  int        jcol;
  int        iend;
  int        i;

  for ( irow = 0; irow < nrows; irow++ )
  {
    sum  = 0.0;
    iend = mat->offset[irow + 1];

    for ( i = mat->offset[irow]; i < iend; i++ )
    {
      jcol = mat->index[i];
      sum += mat->value[i] * rhs[jcol];
    }

    lhs[irow] = sum;
  }
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

  ( void )

{
  const int        niter = 1000;
  const char*      fname = "matrix.dat";
  double*          lhs   = NULL;
  double*          rhs   = NULL;

  sparse_matrix_t  matrix;
  int              iiter;
  double           t0;

  printf ( "Reading matrix from `%s\' ...\n\n", fname );

  sparse_matrix_read ( &matrix, fname );

  printf ( "  nrows : %d\n",   matrix.nrows );
  printf ( "  ncols : %d\n",   matrix.ncols );
  printf ( "  nnz   : %d\n\n", matrix.offset[matrix.nrows] );

  printf ( "Initialising the first vector ...\n" );

  lhs = malloc ( matrix.nrows * sizeof(*lhs) );
  rhs = malloc ( matrix.ncols * sizeof(*rhs) );

  if ( (lhs == NULL) || (rhs == NULL) )
  {
    fprintf ( stderr, "ERROR: failed to allocate the vectors.\n" );
    return 1;
  }

  printf ( "Executing %d matrix-vector products ...\n", niter );

  t0 = wtime ();

  for ( iiter = 0; iiter < niter; iiter++ )
  {
    double*  tmp = rhs;

    matvec ( lhs, &matrix, rhs );

    /* Swap the left-hand side and right-hand side vectors. */

    rhs = lhs;
    lhs = tmp;
  }

  printf ( "Done in %g seconds.\n", wtime() -t0 );

  free   ( lhs );
  free   ( rhs );

  sparse_matrix_destroy ( &matrix );

  return 0;
}
