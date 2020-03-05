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
int a[n], b[n];
long int sum;
#pragma omp parallel for shared(a,b)
for (int i=0; i<n; i++)
a[i] = b[i] = i;
#pragma omp parallel for shared(a,b) reduction(+:sum)
for (int i=0; i < n; i++)
sum = sum + (a[i] * b[i]);
printf("Sum = %ld\n", sum);



    return 0;
}
