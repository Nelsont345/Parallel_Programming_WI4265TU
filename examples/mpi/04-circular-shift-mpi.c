
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char** argv )
{
  const int    N = 20;

  MPI_Request  req[2];
  double*      data;
  int          proc_count;
  int          my_rank;
  int          i, k, n;

  MPI_Init      ( &argc, &argv );
  MPI_Comm_size ( MPI_COMM_WORLD, &proc_count );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  if ( proc_count > N )
  {
    fprintf ( stderr, "Error: too many processes.\n" );
    return 1;
  }

  /* Initialize the sub-array for this process. */

  n    = N / proc_count;
  data = malloc ( n * sizeof(*data) );
  k    = my_rank * n;

  for ( i = 0; i < n; i++ )
  {
    data[i] = k + i;
  }

  /* Print the initial array. */

  if ( my_rank == 0 )
  {
    printf ( "Initial array:\n\n" );
  }

  for ( i = 0; i < n; i++ )
  {
    printf ( "  a[%2d] = %g\n", i + k, data[i] );
  }

  /* Continue here: perform the circular array shift. */

  /* Print the final array. */

  if ( my_rank == 0 )
  {
    printf ( "\nFinal array:\n\n" );
  }

  for ( i = 0; i < n; i++ )
  {
    printf ( "  a[%2d] = %g\n", i + k, data[i] );
  }

  free ( data );

  MPI_Finalize ();

  return 0;
}
