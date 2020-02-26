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
    int          M=0;
    int          nproc;

    parse_args ( &conf,  argc,  argv );

    /* Monte Carlo calculation of PI */
    for (i=0; i<conf.steps; i++)
    {
        double x = rand()/(double)RAND_MAX;
        double y = rand()/(double)RAND_MAX;

        if (x*x + y*y < 1.0)
            M++;
    }

    /* Output */
    printf("Approximation of PI = %g\n", 4*M/(double)conf.steps);

    return 0;
}
