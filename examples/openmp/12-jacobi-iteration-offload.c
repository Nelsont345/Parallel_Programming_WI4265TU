#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main ( int argc, char** argv )
{
  const int    N = 500;
  const int    M = 500;

  double       A[N][M];
  double       B[N][M];
    
  /* Initialize the matrix */
  for( int j = 0; j < N; j++) {
    for( int i = 0; i < M; i++ ) {
      A[j][i] = rand() / (double) RAND_MAX;
    }
  }

  const double tol = 1e-8;
  double       err = 1.0;

  const int    iter_max = 1000;
  int          iter     = 0;

  while ( err > tol && iter < iter_max ) {
    
    /* Reset the error */
    err = 0.0;
    
    /* Update values */
    for( int j = 1; j < N-1; j++) {
      for(int i = 1; i < M-1; i++) {
        
        B[j][i] = 0.25 * (A[j][i+1] + A[j][i-1] +
                          A[j-1][i] + A[j+1][i]);
        
        err = fmax(err, fabs(B[j][i]-A[j][i]));
        
      }  
    }
    
    /* Exchange values */
    for( int j = 1; j < N-1; j++) {
      for( int i = 1; i < M-1; i++ ) {
        
        A[j][i] = B[j][i];
        
      }
    }
    
    if(iter++ % 100 == 0) printf("%5d, %g\n", iter, err);
    
  }
  
  printf("%5d, %g\n", iter, err);
  
}
