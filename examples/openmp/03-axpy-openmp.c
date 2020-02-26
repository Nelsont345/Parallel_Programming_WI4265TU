#include<stdio.h>

#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main( int argc, char** argv )
{
    const int n=1000;
    const int alpha=2;
    int x[n],y[n];

    /* Initialization */
    for (int i=0; i<n; i++)
    {
        x[i] = i; y[i]= i ;
    }

    /* Sequential axpy */
    for (int i=0; i<n; i++)
    {
        y[i] += alpha*x[i];
    }

    if (n<10)
    {
        printf("AXPY:\n");
        for (int i=0; i<n; i++)
        {
            printf("%d ", y[i]);
        }
    }
    else
        printf("AXPY:\nSet N<10 to produce output\n");

    return 0;
}
