
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

/* ---------------------------------------------------------------------
 * types & constants
 * ------------------------------------------------------------------ */

#define                   NTHREADS  9

struct                    barrier
{
  /* Continue here ... */
};

typedef struct barrier   barrier_t;

/* ---------------------------------------------------------------------
 * barrier_init()
 *
 *   Initialises a barrier object. The parameter "nt" specifies
 *   the number of threads that will participate in a barrier
 *   operation.
 * ------------------------------------------------------------------ */

void                      barrier_init

  ( barrier_t*              bar,
    int                     nt )

{
  assert ( bar && (nt > 0) );

  /* Continue here ... */
}

/* ---------------------------------------------------------------------
 * barrier_destroy()
 *
 *   Destroys a barrier object.
 * ------------------------------------------------------------------ */

void                      barrier_destroy

  ( barrier_t*              bar )

{
  assert ( bar );

  /* Continue here ... */
}

/* ---------------------------------------------------------------------
 * barrier_wait()
 *
 *   Blocks the calling threads until the last thread has entered
 *   this function.  The number of threads calling this function must
 *   be equal to the parameter "nt" specified in the call to the
 *   barrier_init() function.
 * ------------------------------------------------------------------ */

void                      barrier_wait

  ( barrier_t*              bar )

{
  assert ( bar );

  /* Continue here ... */
}

/* ---------------------------------------------------------------------
 * thread_func()
 *
 *   The thread entry point. This function performs a number of
 *   barrier operations.
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
