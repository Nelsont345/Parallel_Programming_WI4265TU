#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main( int argc, char** argv )
{
    const int N=1000;
    const int M=10;
    int hist[M];
    long int sum;

  /* Continue here ... */

    /* Output */
    for (int i=0; i<M; i++)
        printf ( "  hist[%3d] = %d\n", i, hist[i] );

    printf ( "  sum       = %ld\n", sum );
    
  return 0;
}
