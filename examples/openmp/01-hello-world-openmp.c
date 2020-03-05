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
  int nthreads, tid;
  omp_set_num_threads(25); //set the number of threads
  #pragma omp parallel private(nthreads, tid)
  {
    tid = omp_get_thread_num();
    printf("Thread number = %d\n", tid);

    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
  }
  return 0;
}
