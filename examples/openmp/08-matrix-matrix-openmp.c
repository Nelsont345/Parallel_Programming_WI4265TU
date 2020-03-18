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
    const int    N = 5;
    const int    M = 5;
    const int    O = 5;

    int *A[N];
    for (int i=0;i<N;i++)
    {
        A[i] = (int *)malloc(sizeof(int)*M);
    }

    int *B[M];
    for (int i=0;i<M;i++)
    {
        B[i] = (int *)malloc(sizeof(int)*O);
    }

    int *C[O];
    for (int i=0;i<O;i++)
    {
        C[i] = (int *)malloc(sizeof(int)*N);
    }



    /* Initialize the matrices. */
    #pragma omp parallel for num_threads(2) collapse(2)
    for ( int i = 0; i < N; i++ )
        for ( int j = 0; j < M; j++ )
            {
                A[i][j] = i+j;
            }

    #pragma omp parallel for num_threads(2) collapse(2)
    for ( int i = 0; i < M; i++ )
        for ( int j = 0; j < O; j++ )
            {
                B[i][j] = i+j;
            }

    

    
    
    for ( int i = 0; i < N; i++ )
        for ( int k = 0; k < O; k++ )
            {   C[i][k] =0;
                for ( int j = 0; j < M; j++ )
                    C[i][k] += A[i][j] * B[j][k];
            }
    
    if (N<10 && O<10)
    {
        printf("Matrix-matrix product:\n");
        for (int i=0; i<N; i++)
        {
            for (int k=0; k<O; k++)
                printf("%d ", C[i][k]);
            printf("\n");
        }
    }
    else
        printf("Matrix-matrix product:\nSet N<10 and O<10 to produce output\n");

    return 0;
}
