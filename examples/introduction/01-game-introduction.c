
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

/* ---------------------------------------------------------------------
 * global variables, constants and types
 * ------------------------------------------------------------------ */

#define                   INIT_TAG      1
#define                   EXCHANGE_TAG  2

#define                   DEBUG_SOME    1
#define                   DEBUG_ALL     2

static int                debug_level = 0;

typedef unsigned char     byte_t;

struct                    conf
{
  int                       dims[2];
  int                       steps;
};

struct                    grid
{
  int                       origin     [2];
  int                       local_dims [2];
  int                       global_dims[2];
  byte_t*                   cells;
};

struct                    xdata
{
  int                       req_count;
  int                       xchg_count;
  byte_t*                   send_buffer;
  byte_t*                   recv_buffer;
  int*                      recv_index;
  int*                      send_index;
  MPI_Request*              send_reqs;
  MPI_Request*              recv_reqs;
};

struct                    proc_info
{
  int                       my_rank;
  int                       my_coords[2];
  int                       proc_dims[2];
};

typedef struct conf       conf_t;
typedef struct grid       grid_t;
typedef struct xdata      xdata_t;
typedef struct proc_info  proc_info_t;

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
  MPI_Abort ( MPI_COMM_WORLD, 1 );
  exit      ( 1 );
}

/* ---------------------------------------------------------------------
 * allocate()
 * ------------------------------------------------------------------ */

void*                     allocate

  ( size_t                  nmemb,
    int                     count )

{
  void*  ptr = NULL;

  if ( count > 0 )
  {
    ptr = calloc ( nmemb, (size_t) count );

    if ( ! ptr )
    {
      error ( "failed to allocate %ld bytes",
              (long) (count * nmemb) );
    }
  }

  return ptr;
}

/* ---------------------------------------------------------------------
 * kill_grid()
 * ------------------------------------------------------------------ */

void                      kill_grid

  ( grid_t*                 grid )

{
  free   ( grid->cells );
  memset ( grid, 0x0, sizeof(*grid) );
}

/* ---------------------------------------------------------------------
 * kill_xdata()
 * ------------------------------------------------------------------ */

void                      kill_xdata

  ( xdata_t*                xdata )

{
  int  i;

  for ( i = 0; i < xdata->req_count; i++ )
  {
    MPI_Request_free ( &xdata->send_reqs[i] );
    MPI_Request_free ( &xdata->recv_reqs[i] );
  }

  free   ( xdata->recv_index );
  free   ( xdata->send_index );
  free   ( xdata->recv_buffer );
  free   ( xdata->send_buffer );
  free   ( xdata->recv_reqs );
  free   ( xdata->send_reqs );

  memset ( xdata, 0x0, sizeof(*xdata) );
}

/* ---------------------------------------------------------------------
 * proc_rank()
 * ------------------------------------------------------------------ */

int                       proc_rank

  ( int                     ipos,
    int                     jpos,
    const proc_info_t*      info )

{
  const int  m = info->proc_dims[0];
  const int  n = info->proc_dims[1];

  if ( (ipos < 0) || (ipos >= m) ||
       (jpos < 0) || (jpos >= n) )
  {
    return -1;
  }
  else
  {
    return (ipos + jpos * m);
  }
}

/* ---------------------------------------------------------------------
 * print_grid()
 * ------------------------------------------------------------------ */

void                      print_grid

  ( const grid_t*           grid )

{
  const int      m   = grid->local_dims[0];
  const int      n   = grid->local_dims[1];
  const byte_t*  row = NULL;

  int            i, j;

  putchar ( '+' );

  for ( i = 0; i < m; i++ )
  {
    putchar ( '-' );
  }

  putchar ( '+' );
  putchar ( '\n' );

  for ( j = n; j >= 1; j-- )
  {
    row = grid->cells + (j * (m + 2));

    putchar ( '|' );

    for ( i = 1; i <= m; i++ )
    {
      if ( row[i] )
      {
        putchar ( 'X' );
      }
      else
      {
        putchar ( ' ' );
      }
    }

    putchar ( '|' );
    putchar ( '\n' );
  }

  putchar ( '+' );

  for ( i = 0; i < m; i++ )
  {
    putchar ( '-' );
  }

  putchar ( '+' );
  putchar ( '\n' );
  putchar ( '\n' );
}

/* ---------------------------------------------------------------------
 * parse_args()
 * ------------------------------------------------------------------ */

void                      parse_args

  ( conf_t*                 conf,
    int                     argc,
    char**                  argv )

{
  const int  root = 0;

  char       dummy;
  int        ibuf[3];
  int        iarg;

  /* Set default values. */

  conf->dims[0] = 16;
  conf->dims[1] = 16;
  conf->steps   = 16;

  for ( iarg = 1; iarg < argc; iarg++ )
  {
    if ( strcmp( argv[iarg], "--dims" ) == 0 )
    {
      iarg++;

      if ( iarg >= argc )
      {
        error ( "no dimensions specified" );
      }

      if ( sscanf( argv[iarg], " %d %c %d",
                   &conf->dims[0], &dummy, &conf->dims[1] ) != 3 ||
           (conf->dims[0] <= 0) || (conf->dims[1] <= 0) )
      {
        error ( "invalid dimensions specified" );
      }

      continue;
    }

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

    if ( strcmp( argv[iarg], "--debug" ) == 0 )
    {
      iarg++;

      if ( iarg >= argc )
      {
        error ( "no debug level specified" );
      }

      if ( sscanf( argv[iarg], " %d", &debug_level ) != 1 ||
           (debug_level < 0) )
      {
        error ( "invalid debug level specified" );
      }

      continue;
    }
  }

  ibuf[0] = conf->dims[0];
  ibuf[1] = conf->dims[1];
  ibuf[2] = conf->steps;

  MPI_Bcast ( ibuf, 3, MPI_INT, root, MPI_COMM_WORLD );

  printf ( "Global dimensions : %d x %d\n",
           conf->dims[0], conf->dims[1] );
  printf ( "Number of steps   : %d\n",
           conf->steps);

  if ( debug_level )
  {
    printf ( "Debug level       : %d\n", debug_level );
  }

  printf ( "\n" );
}

/* ---------------------------------------------------------------------
 * recv_conf()
 * ------------------------------------------------------------------ */

void                      recv_conf

  ( conf_t*                 conf )

{
  const int  root = 0;

  int        ibuf[3];

  MPI_Bcast ( ibuf, 3, MPI_INT, root, MPI_COMM_WORLD );

  conf->dims[0] = ibuf[0];
  conf->dims[1] = ibuf[1];
  conf->steps   = ibuf[2];
}

/* ---------------------------------------------------------------------
 * init_grid()
 * ------------------------------------------------------------------ */

void                      init_grid

  ( grid_t*                 grid,
    const conf_t*           conf )

{
  const int  m   = conf->dims[0];
  const int  n   = conf->dims[1];
  byte_t*    row = NULL;

  int        i, j;

  if ( debug_level )
  {
    printf ( "Initializing grid ...\n" );
  }

  grid->origin     [0] = 0;
  grid->origin     [1] = 0;
  grid->local_dims [0] = m;
  grid->local_dims [1] = n;
  grid->global_dims[0] = m;
  grid->global_dims[1] = n;

  /* Note that the grid is bordered by a strip of halo cells. */

  grid->cells = (byte_t*) allocate ( sizeof(*grid->cells), (m + 2) * (n + 2) );

  for ( j = 1; j <= n; j++ )
  {
    row = grid->cells + (j * (m + 2));

    for ( i = 1; i <= m; i++ )
    {
      int  v = rand ();

      if ( v > (RAND_MAX / 2) )
      {
        row[i] = 1;
      }
      else
      {
        row[i] = 0;
      }
    }
  }

  if ( debug_level >= DEBUG_ALL )
  {
    printf     ( "Initial grid:\n\n" );
    print_grid ( grid );
  }
}

/* ---------------------------------------------------------------------
 * init_xdata()
 * ------------------------------------------------------------------ */

void                      init_xdata

  ( xdata_t*                xdata,
    const grid_t*           grid,
    const proc_info_t*      info )

{
  const int     m           = grid->local_dims[0];
  const int     n           = grid->local_dims[1];

  MPI_Request*  send_reqs   = NULL;
  MPI_Request*  recv_reqs   = NULL;

  byte_t*       send_buffer = NULL;
  byte_t*       recv_buffer = NULL;
  int*          send_index  = NULL;
  int*          recv_index  = NULL;

  int           xchg_count  = 2 * m + 2 * n + 4;
  int           req_count   = 8;
  int           iproc       = 0;

  int           xidx[9];
  int           rank[8];
  int           i, j;

  send_reqs   = (MPI_Request*) allocate ( sizeof(*send_reqs),   req_count );
  recv_reqs   = (MPI_Request*) allocate ( sizeof(*recv_reqs),   req_count );
  send_buffer = (byte_t*)      allocate ( sizeof(*send_buffer), xchg_count );
  recv_buffer = (byte_t*)      allocate ( sizeof(*recv_buffer), xchg_count );
  send_index  = (int*)         allocate ( sizeof(*send_index),  xchg_count );
  recv_index  = (int*)         allocate ( sizeof(*recv_index),  xchg_count );

  xchg_count  = 0;

  /* Lower-left cell. */

  rank[iproc]   = proc_rank ( info->my_coords[0] - 1,
                              info->my_coords[1] - 1, info );
  xidx[iproc++] = xchg_count;

  recv_index[xchg_count]   = 0;
  send_index[xchg_count++] = m + 3;

  /* Lower border. */

  rank[iproc]   = proc_rank ( info->my_coords[0],
                              info->my_coords[1] - 1, info );
  xidx[iproc++] = xchg_count;

  for ( i = 1; i <= m; i++ )
  {
    recv_index[xchg_count]   = i;
    send_index[xchg_count++] = i + m + 2;
  }

  /* Lower-right cell. */

  rank[iproc]   = proc_rank ( info->my_coords[0] + 1,
                              info->my_coords[1] - 1, info );
  xidx[iproc++] = xchg_count;

  recv_index[xchg_count]   = m + 1;
  send_index[xchg_count++] = 2 * m + 2;

  /* Right border. */

  rank[iproc]   = proc_rank ( info->my_coords[0] + 1,
                              info->my_coords[1],     info );
  xidx[iproc++] = xchg_count;

  for ( j = 1; j <= n; j++ )
  {
    recv_index[xchg_count]   = m + 1 + j * (m + 2);
    send_index[xchg_count++] = m     + j * (m + 2);
  }

  /* Upper-right cell. */

  rank[iproc]   = proc_rank ( info->my_coords[0] + 1,
                              info->my_coords[1] + 1, info );
  xidx[iproc++] = xchg_count;

  recv_index[xchg_count]   = (m + 2) * (n + 2) - 1;
  send_index[xchg_count++] = (m + 2) * (n + 1) - 2;

  /* Upper border. */

  rank[iproc]   = proc_rank ( info->my_coords[0],
                              info->my_coords[1] + 1, info );
  xidx[iproc++] = xchg_count;

  for ( i = 1; i <= m; i++ )
  {
    recv_index[xchg_count]   = (m + 2) * (n + 1) + i;
    send_index[xchg_count++] = (m + 2) *  n      + i;
  }

  /* Upper-left cell. */

  rank[iproc]   = proc_rank ( info->my_coords[0] - 1,
                              info->my_coords[1] + 1, info );
  xidx[iproc++] = xchg_count;

  recv_index[xchg_count]   = (m + 2) * (n + 1);
  send_index[xchg_count++] = (m + 2) *  n + 1;

  /* Left border. */

  rank[iproc]   = proc_rank ( info->my_coords[0] - 1,
                              info->my_coords[1],     info );
  xidx[iproc++] = xchg_count;

  for ( j = 1; j <= n; j++ )
  {
    recv_index[xchg_count]   =     j * (m + 2);
    send_index[xchg_count++] = 1 + j * (m + 2);
  }

  xidx[iproc] = xchg_count;

  assert ( iproc      == 8 );
  assert ( xchg_count == (2 * m + 2 * n + 4) );

  xchg_count = 0;
  req_count  = 0;

  for ( iproc = 0; iproc < 8; iproc++ )
  {
    if ( rank[iproc] >= 0 )
    {
      i = xidx[iproc];
      j = xidx[iproc + 1];

      MPI_Send_init ( &send_buffer[xchg_count], (j - i), MPI_BYTE,
                      rank[iproc], EXCHANGE_TAG, MPI_COMM_WORLD,
                      &send_reqs[req_count] );

      MPI_Recv_init ( &recv_buffer[xchg_count], (j - i), MPI_BYTE,
                      rank[iproc], EXCHANGE_TAG, MPI_COMM_WORLD,
                      &recv_reqs[req_count] );

      req_count++;

      for ( ; i < j; i++, xchg_count++ )
      {
        recv_index[xchg_count] = recv_index[i];
        send_index[xchg_count] = send_index[i];
      }
    }
  }

  xdata->req_count   = req_count;
  xdata->xchg_count  = xchg_count;
  xdata->recv_buffer = recv_buffer;
  xdata->send_buffer = send_buffer;
  xdata->recv_index  = recv_index;
  xdata->send_index  = send_index;
  xdata->recv_reqs   = recv_reqs;
  xdata->send_reqs   = send_reqs;
}

/* ---------------------------------------------------------------------
 * exchange()
 * ------------------------------------------------------------------ */

void                      exchange

  ( grid_t*                 grid,
    xdata_t*                xdata )

{
  const int      xchg_count     = xdata->xchg_count;

  const int*     index          = NULL;
  const byte_t*  rhs            = NULL;
  byte_t*        lhs            = NULL;

  int            i;

  MPI_Startall ( xdata->req_count, xdata->recv_reqs );

  /* Load the send buffer. */

  index = xdata->send_index;
  lhs   = xdata->send_buffer;
  rhs   = grid->cells;

  for ( i = 0; i < xchg_count; i++ )
  {
    lhs[i] = rhs[index[i]];
  }

  MPI_Startall ( xdata->req_count, xdata->send_reqs );

  /* Wait for the send requests to complete and copy the receive
   * buffer to the grid. */

  index = xdata->recv_index;
  lhs   = grid->cells;
  rhs   = xdata->recv_buffer;

  MPI_Waitall ( xdata->req_count, xdata->recv_reqs,
                MPI_STATUSES_IGNORE );

  for ( i = 0; i < xchg_count; i++ )
  {
    lhs[index[i]] = rhs[i];
  }

  /* Wait for the send requests to complete. */

  MPI_Waitall ( xdata->req_count, xdata->send_reqs,
                MPI_STATUSES_IGNORE );
}

/* ---------------------------------------------------------------------
 * part_grid()
 * ------------------------------------------------------------------ */

void                      part_grid

  ( proc_info_t*            info,
    grid_t*                 grid,
    grid_t*                 grid0 )

{
  const int  m0    = grid0->global_dims[0];
  const int  n0    = grid0->global_dims[1];

  byte_t*    cells = NULL;
  byte_t*    row   = NULL;

  int        ibuf[10];
  int        count;
  int        rank;
  int        diff;
  int        mproc, nproc;
  int        iproc, jproc;
  int        i0,    i1;
  int        j0,    j1;
  int        m,     n;
  int        i,     j;
  int        k;

  MPI_Comm_size ( MPI_COMM_WORLD, &count );

  info->my_rank      = 0;
  info->my_coords[0] = 0;
  info->my_coords[1] = 0;

  /* Determine the optimal processor grid dimensions. */

  mproc = -1;
  nproc = -1;
  diff  = -1;

  for ( j = 1; j <= n0; j++ )
  {
    for ( i = 1; i <= m0; i++ )
    {
      if ( (i * j) == count )
      {
        if ( (diff < 0) || (abs( i - j ) < diff) )
        {
          mproc = i;
          nproc = j;
          diff  = abs ( i - j );
        }
      }
    }
  }

  if ( diff < 0 )
  {
    error ( "more processors than cells specified" );
  }

  info->proc_dims[0] = mproc;
  info->proc_dims[1] = nproc;

  if ( debug_level )
  {
    printf ( "Processor grid : %d x %d\n\n", mproc, nproc );
    printf ( "Distributing partitions ...\n" );
  }

  /* Partition the grid and distribute it to the other processes. */

  j0 = 0;

  for ( jproc = 0; jproc < nproc; jproc++ )
  {
    n  = (n0 - j0) / (nproc - jproc);
    j1 = j0 + n;
    i0 = 0;

    assert ( (j1 > j0) && (j1 <= n0) );

    for ( iproc = 0; iproc < mproc; iproc++ )
    {
      rank  = proc_rank ( iproc, jproc, info );
      m     = (m0 - i0) / (mproc - iproc);
      i1    = i0 + m;

      assert ( (i1 > i0) && (i1 <= m0) );

      cells = (byte_t*) allocate ( sizeof(*cells), (m + 2) * (n + 2) );
      k     = 0;

      for ( j = j0 - 1; j <= j1; j++ )
      {
        row = grid0->cells + ((j + 1) * (m0 + 2) + 1);

        for ( i = i0 - 1; i <= i1; i++ )
        {
          cells[k++] = row[i];
        }
      }

      if ( rank == 0 )
      {
        grid->origin     [0] = i0;
        grid->origin     [1] = j0;
        grid->local_dims [0] = m;
        grid->local_dims [1] = n;
        grid->global_dims[0] = m0;
        grid->global_dims[1] = n0;
        grid->cells          = cells;
      }
      else
      {
        ibuf[0] = iproc;
        ibuf[1] = jproc;
        ibuf[2] = mproc;
        ibuf[3] = nproc;
        ibuf[4] = i0;
        ibuf[5] = j0;
        ibuf[6] = m;
        ibuf[7] = n;
        ibuf[8] = m0;
        ibuf[9] = n0;

        MPI_Send ( ibuf, 10, MPI_INT, rank,
                   INIT_TAG, MPI_COMM_WORLD );

        MPI_Send ( cells, (m + 2) * (n + 2), MPI_BYTE, rank,
                   INIT_TAG, MPI_COMM_WORLD );

        free ( cells );
      }

      i0 = i1;
    }

    j0 = j1;
  }
}

/* ---------------------------------------------------------------------
 * recv_grid()
 * ------------------------------------------------------------------ */

void                      recv_grid

  ( proc_info_t*            info,
    grid_t*                 grid )

{
  const int   rank = 0;

  MPI_Status  status;
  int         ibuf[10];
  int         m, n;

  MPI_Recv ( ibuf, 10, MPI_INT, rank,
             INIT_TAG, MPI_COMM_WORLD, &status );

  info->my_coords  [0] = ibuf[0];
  info->my_coords  [1] = ibuf[1];
  info->proc_dims  [0] = ibuf[2];
  info->proc_dims  [1] = ibuf[3];
  grid->origin     [0] = ibuf[4];
  grid->origin     [1] = ibuf[5];
  grid->local_dims [0] = ibuf[6];
  grid->local_dims [1] = ibuf[7];
  grid->global_dims[0] = ibuf[8];
  grid->global_dims[1] = ibuf[9];

  m = grid->local_dims[0];
  n = grid->local_dims[1];

  grid->cells = (byte_t*) allocate ( sizeof(*grid->cells), (m + 2) * (n + 2) );

  MPI_Recv ( grid->cells, (m + 2) * (n + 2), MPI_BYTE, rank,
             INIT_TAG, MPI_COMM_WORLD, &status );

  if ( debug_level >= DEBUG_ALL )
  {
    printf     ( "\nGrid at process %d:\n\n", info->my_rank );
    print_grid ( grid );
  }
}

/* ---------------------------------------------------------------------
 * run_step()
 * ------------------------------------------------------------------ */

void                      run_step

  ( grid_t*                 grid,
    byte_t**                work )

{
  static const byte_t  TRANS_TABLE[9][2] =
  {
    { 0, 0 },  /* Cells with less than 2 live neighbors die. */
    { 0, 0 },  /* Cells with less than 2 live neighbors die. */
    { 0, 1 },  /* A live cell with 2 live neighbors lives. */
    { 1, 1 },  /* Cells with 3 live neighbors live. */
    { 0, 0 },  /* Cells with more than 3 live neighbors die. */
    { 0, 0 },  /* Cells with more than 3 live neighbors die. */
    { 0, 0 },  /* Cells with more than 3 live neighbors die. */
    { 0, 0 },  /* Cells with more than 3 live neighbors die. */
    { 0, 0 },  /* Cells with more than 3 live neighbors die. */
  };

  const int      m = grid->local_dims[0];
  const int      n = grid->local_dims[1];

  const byte_t*  rhs = NULL;
  byte_t*        lhs = NULL;
  byte_t*        tmp = NULL;

  int            i, j;
  byte_t         k;

  for ( j = 1; j <= n; j++ )
  {
    lhs = (*work)     + (j * (m + 2));
    rhs = grid->cells + (j * (m + 2));

    for ( i = 1; i <= m; i++ )
    {
      k      = (rhs[i - m - 3] +
                rhs[i - m - 2] +
                rhs[i - m - 1] +
                rhs[i - 1]     +
                rhs[i + 1]     +
                rhs[i + m + 1] +
                rhs[i + m + 2] +
                rhs[i + m + 3]);

      lhs[i] = TRANS_TABLE[k][rhs[i]];
    }
  }

  tmp         = grid->cells;
  grid->cells = *work;
  *work       = tmp;
}

/* ---------------------------------------------------------------------
 * run_game()
 * ------------------------------------------------------------------ */

void                      run_game

  ( xdata_t*                xdata,
    grid_t*                 grid,
    const conf_t*           conf )

{
  const int  m = grid->local_dims[0];
  const int  n = grid->local_dims[1];

  byte_t*    work;
  int        istep;

  if ( debug_level )
  {
    printf ( "Starting simulation ...\n" );

    if ( debug_level >= DEBUG_ALL )
    {
      printf ( "\n" );
    }
  }

  work = (byte_t*) allocate ( sizeof(*work), (m + 2) * (n + 2) );

  for ( istep = 0; istep < conf->steps; istep++ )
  {
    exchange ( grid, xdata );
    run_step ( grid, &work );

    if ( debug_level >= DEBUG_ALL )
    {
      printf     ( "\nStep %d\n\n", istep );
      print_grid ( grid );
      usleep     ( 400 * 1000 );
    }
  }

  free ( work );
}

/* ---------------------------------------------------------------------
 * run_worker()
 * ------------------------------------------------------------------ */

void                      run_worker

  ( int                     my_rank )

{
  proc_info_t  info;
  conf_t       conf;
  grid_t       grid;
  xdata_t      xdata;

  memset ( &info,  0x0, sizeof(info) );
  memset ( &conf,  0x0, sizeof(conf) );
  memset ( &grid,  0x0, sizeof(grid) );
  memset ( &xdata, 0x0, sizeof(xdata) );

  info.my_rank = my_rank;

  recv_conf  ( &conf );
  recv_grid  ( &info,  &grid );
  init_xdata ( &xdata, &grid, &info );
  run_game   ( &xdata, &grid, &conf );
  kill_grid  ( &grid );
  kill_xdata ( &xdata );
}

/* ---------------------------------------------------------------------
 * run_master()
 * ------------------------------------------------------------------ */

void                      run_master

  ( int                     argc,
    char**                  argv )

{
  proc_info_t  info;
  conf_t       conf;
  grid_t       grid0;
  grid_t       grid;
  xdata_t      xdata;
  double       time0;

  memset ( &info,  0x0, sizeof(info) );
  memset ( &conf,  0x0, sizeof(conf) );
  memset ( &grid0, 0x0, sizeof(grid0) );
  memset ( &grid,  0x0, sizeof(grid) );
  memset ( &xdata, 0x0, sizeof(xdata) );

  time0 = MPI_Wtime ();

  parse_args ( &conf,  argc,  argv );
  init_grid  ( &grid0, &conf );
  part_grid  ( &info,  &grid, &grid0 );
  kill_grid  ( &grid0 );
  init_xdata ( &xdata, &grid, &info );
  run_game   ( &xdata, &grid, &conf );
  kill_grid  ( &grid );
  kill_xdata ( &xdata );

  printf ( "Finished in %g seconds.\n\n", (MPI_Wtime() - time0) );
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int                       main

  ( int                     argc,
    char**                  argv )

{
  int  my_rank;

  MPI_Init      ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );

  if ( my_rank == 0 )
  {
    run_master ( argc, argv );
  }
  else
  {
    run_worker ( my_rank );
  }

  MPI_Finalize ();

  return 0;
}

