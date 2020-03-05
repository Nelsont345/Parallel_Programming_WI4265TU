#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef _OPENMP
#include "omp.h"
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

/* ---------------------------------------------------------------------
 * global variables, constants and types
 * ------------------------------------------------------------------ */


static struct { float float_val1; float float_val2; } tuple[7];

struct                      conf
{
  int                       steps;
};

typedef struct conf       conf_t;

/* ---------------------------------------------------------------------
 * error()
 * ------------------------------------------------------------------ */

void                      error

  ( const char*             fmt, ... )

{
  va_list  ap;

  va_start  ( ap, fmt );
  fprintf   ( stderr, "\n*** ERROR: " );
  vfprintf  ( stderr, fmt, ap );
  fprintf   ( stderr, "\n\n" );
  va_end    ( ap );
  exit      ( 1 );
}

/* ---------------------------------------------------------------------
 * parse_args()
 * ------------------------------------------------------------------ */

void parse_args

  ( conf_t*                 conf,
    int                     argc,
    char**                  argv )

{
    const int  root = 0;

    int        iarg;

    /* Set default values. */

    conf->steps  = 1000;

    for ( iarg = 1; iarg < argc; iarg++ )
    {
        if ( strcmp( argv[iarg], "--steps" ) == 0 )
        {
            iarg++;

            if ( iarg >= argc )
            {
                error ( "no number of steps specified" );
            }

            if ( sscanf( argv[iarg], " %d", &conf->steps ) != 1 ||
                 (conf->steps < 0) )
            {
                error ( "invalid number of steps specified" );
            }

            continue;
        }
    }
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

  ( int                     argc,
    char**                  argv )

{
    conf_t       conf;
    int          i;
    int          j;
    int          M=0;
    int          nproc;

    parse_args ( &conf,  argc,  argv );

    /* Monte Carlo calculation of PI */
  /*
    
    for (i=0; i<conf.steps; i++)
    {
        double x = rand()/(double)RAND_MAX;
        double y = rand()/(double)RAND_MAX;

        if (x*x + y*y < 1.0)
            M++;
    }
  */
    /* Output */
    //printf("Approximation of PI = %g\n", 4*M/(double)conf.steps);


    tuple[0].float_val1 = 0.8;
    tuple[0].float_val2 = 0.0;

    tuple[1].float_val1 = 0.8;
    tuple[1].float_val2 = 0.2;

    tuple[2].float_val1 = 0.8;
    tuple[2].float_val2 = 0.4;

    tuple[3].float_val1 = 0.6;
    tuple[3].float_val2 = 0.6;

    tuple[4].float_val1 = 0.0;
    tuple[4].float_val2 = 0.8;

    tuple[5].float_val1 = 0.2;
    tuple[5].float_val2 = 0.8;

    tuple[6].float_val1 = 0.2;
    tuple[6].float_val2 = 0.8;


    printf("Tuple %d is: %f \n", 0, tuple[0].float_val1);
    
    // for every value generated inside the 7 boundary squares, 15/7 are generated inside, and 5/7 generated outside
    #pragma omp parallel for shared(M)
    for (j=0; j<7; j++)
    {
      for (i=0; i<conf.steps/7; i++)    //repeat foreach of the 7 squares
      {
    
        double x = tuple[j].float_val1 + (rand()*0.2)/(double)RAND_MAX;
        double y = tuple[j].float_val2 +(rand()*0.2)/(double)RAND_MAX;

      if (x*x + y*y < 1.0)
          {
          M++;
          }
      }
    }
    printf("%d and %d \n", M, conf.steps);
    printf("Approximation of PI = %g\n", (28*M + 60*(double)conf.steps)/(25*(double)conf.steps));
    return 0;
}
