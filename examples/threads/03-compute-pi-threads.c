
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* ---------------------------------------------------------------------
 * global variables, constants and types
 * ------------------------------------------------------------------ */

struct                    conf
{
  int                       niter;
  int                       nthreads;
};

typedef struct conf       conf_t;

/* ---------------------------------------------------------------------
 * error()
 * ------------------------------------------------------------------ */

void                      error

  ( const char*             fmt, ... )

{
  va_list  ap;

  va_start ( ap, fmt );
  fprintf  ( stderr, "\n*** ERROR: " );
  vfprintf ( stderr, fmt, ap );
  fprintf  ( stderr, "\n\n" );
  va_end   ( ap );
  exit     ( 1 );
}

/* ---------------------------------------------------------------------
 * parse_args()
 * ------------------------------------------------------------------ */

void parse_args

  ( conf_t*                 conf,
    int                     argc,
    char**                  argv )

{
  int  iarg;

  /* Set default values. */

  conf->niter    = 1000;
  conf->nthreads = 1;

  for ( iarg = 1; iarg < argc; iarg++ )
  {
    if ( strcmp( argv[iarg], "--niter" ) == 0 )
    {
      iarg++;

      if ( iarg >= argc )
      {
        error ( "missing number of iterations" );
      }

      if ( sscanf( argv[iarg], " %d", &conf->niter ) != 1 ||
           (conf->niter < 0) )
      {
        error ( "invalid number of iterations specified" );
      }

      continue;
    }

    if ( strcmp( argv[iarg], "--nthreads" ) == 0 )
    {
      iarg++;

      if ( iarg >= argc )
      {
        error ( "missing number of threads" );
      }

      if ( sscanf( argv[iarg], " %d", &conf->nthreads ) != 1 ||
           (conf->niter < 1) )
      {
        error ( "invalid number of threads specified" );
      }

      continue;
    }

    error ( "invalid argument: %s", argv[iarg] );
  }

  /* Make sure that the number of iterations is divisible by the
   * number of threads. */

  conf->niter = (conf->niter / conf->nthreads) * conf->nthreads;
}

/* ---------------------------------------------------------------------
 * thread_func()
 * ------------------------------------------------------------------ */

void*                     thread_func

  ( void*                   arg )

{
  /* Do the parallel Monte Carlo calculation of PI here. */

  return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

  ( int                     argc,
    char**                  argv )

{
  conf_t  conf;
  int     i, m;

  parse_args ( &conf, argc, argv );

  /* Monte Carlo calculation of PI; move this to the function
   * thread_func. */

  for ( i = 0, m = 0; i < conf.niter; i++ )
  {
    double  x = rand () / (double) RAND_MAX;
    double  y = rand () / (double) RAND_MAX;

    if ( (x*x +  y*y) < 1.0 )
    {
      m++;
    }
  }

  printf ( "Parallel approximation of PI = %g.\n",
           4 * m / (double) conf.niter );

  return 0;
}
