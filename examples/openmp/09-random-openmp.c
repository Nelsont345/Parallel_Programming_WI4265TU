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
    /* Start your implementation here */
    printf("Output\n");
    
    return 0;
}
