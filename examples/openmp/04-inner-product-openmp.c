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
    int x[n],y[n];
    long int ip=0;

    /* Initialization */
    for (int i=0; i<n; i++)
    {
        x[i] = i; y[i]= i ;
    }

    /* Sequential inner product */
    for (int i=0; i<n; i++)
    {
        ip += x[i]*y[i];
    }

    printf("Inner product: %ld\n", ip);
    
    return 0;
}
