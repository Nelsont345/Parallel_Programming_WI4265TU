
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

/* ---------------------------------------------------------------------
 * types & constants
 * ------------------------------------------------------------------ */

#define                   NTHREADS  9

struct                    reduction
{
  /* Continue here ... */
};

typedef struct reduction  reduction_t;

/* ---------------------------------------------------------------------
 * reduction_init()
 *
 *   Initialises a reduction variable. The parameter "nt" specifies
 *   the number of threads that will participate in a reduction
 *   operation.
 * ------------------------------------------------------------------ */

void                      reduction_init

  ( reduction_t*            red,
    int                     nt )

{
  assert ( red && (nt > 0) );

  /* Continue here ... */
}

/* ---------------------------------------------------------------------
 * reduction_destroy()
 *
 *   Destroys a reduction variable.
 * ------------------------------------------------------------------ */

void                      reduction_destroy

  ( reduction_t*            red )

{
  assert ( red );

  /* Continue here ... */
}

/* ---------------------------------------------------------------------
 * reduction_sum()
 *
 *   Calculates a global sum across multiple threads. The number
 *   of threads calling this function must be equal to the
 *   parameter "nt" specified in the call to the reduction_init()
 *   function.
 * ------------------------------------------------------------------ */

double                    reduction_sum

  ( reduction_t*            red,
    double                  val )

{
  assert ( red );

  double  result = 0.0;

  /* Continue here ... */

  return result;
}

/* ---------------------------------------------------------------------
 * thread_func()
 *
 *   The thread entry point. This function performs a number of
 *   reduction operations.
 * ------------------------------------------------------------------ */

void*                     thread_func

  ( void*                   arg )

{
  /* Continue here ... */

  return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

( int                     argc,
  char**                  argv )


{
  /* Continue here ... */

  return 0;
}
