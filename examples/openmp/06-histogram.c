#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#ifdef _OPENMP
#include<omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

int main( int argc, char** argv )
{
    const int N=1000000;
    const int M=10;
    int *hist[M]; 
    for (int i=0;i<M;i++)
    {
        hist[i] = malloc(sizeof(int));
    }
    int *r[N];
    for (int i=0;i<N;i++)
    {
        r[i] = malloc(sizeof(int));
    }



    for (int i=0; i<N; i++)
    {
      *r[i] = rand() % M;
    }


    #pragma omp for
    for (int i=0; i<M; i++)
    {
      *hist[i] = 0;
    }

    #pragma omp parallel shared(hist)

    #pragma omp for
    for (int i=0; i<N; i++)
      #pragma omp critical  //prevent the programme from writing to an address, if it is beig used
      {*hist[*r[i]] += 1;
      } 

    /* Output */
    for (int i=0; i<M; i++)
        printf ( "  hist[%3d] = %d\n", i, *hist[i] );
  return 0;
}
