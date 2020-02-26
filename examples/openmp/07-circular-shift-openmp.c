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
    const int    N = 10;
    double       a[N];
    double       t;
    int          i;

    /* Initialize the array. */

    for ( i = 0; i < N; i++ )
        {
            a[i] = i;
        }

    /* Print the initial array. */

    printf("Initial array:\n");
    for ( i = 0; i < N; i++ )
        {
            printf ( "  a[%3d] = %g\n", i, a[i] );
        }

    /* Continue here: perform the circular array shift. */

    

    /* Print the final array. */

    printf("\nFinal array:\n");
    for ( i = 0; i < N; i++ )
        {
            printf ( "  a[%3d] = %g\n", i, a[i] );
        }

    return 0;
}
