#include<stdio.h>
#include<stdlib.h>
#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main( int argc, char** argv )
{
    const int n=10000;
    int  *x = malloc(sizeof(int)*n);
    int  *y = malloc(sizeof(int)*n);
    int *d[n];
    for (int i=0;i<n;i++)
    {
        d[i] = (int *)malloc(sizeof(int)*n);
    }

 
    #pragma omp parallel for shared(x, y)
        for (int i=0; i<n; i++)
        {
            x[i] = i; y[i]= i ;
        }

    #pragma omp parallel for shared(d, x, y) schedule(static, 7373) collapse(2)
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
    {
        d[i][j] = x[i]*y[j];
    }
   
    if (n<10)
    {
        
        printf("Dyadic product:\n");
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)            
                printf("%d ", d[i][j]);
            printf("\n");
        }
    }
    else
        printf("Dyadic product:\nSet N<10 to produce output\n");
        
    return 0;
}
