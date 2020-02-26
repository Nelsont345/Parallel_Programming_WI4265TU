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
    const int    O = 500;
    
    double       A[N][M];
    double       B[M][O];
    double       C[N][O];

    /* Initialize the matrices. */

    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            {
                A[i][j] = i+j;
            }

    for ( int i = 0; i < M; i++ )
        for ( int j = 0; j < O; j++ )
            {
                B[i][j] = i+j;
            }

    /* Sequential matrix-matrix multiplication. */

    for ( int i = 0; i < N; i++ )
        for ( int k = 0; k < O; k++ )
            {
                for ( int j = 0; j < M; j++ )
                    C[i][k] += A[i][j] * B[j][k];
            }
    
    if (N<10 && O<10)
    {
        printf("Matrix-matrix product:\n");
        for (int i=0; i<N; i++)
        {
            for (int k=0; k<O; k++)
                printf("%f ", C[i][k]);
            printf("\n");
        }
    }
    else
        printf("Matrix-matrix product:\nSet N<10 and O<10 to produce output\n");

    return 0;
}
