#include<stdio.h>
            
#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main(int argc, char** argv)
{
  /* Continue here ... */

  return 0;
}
