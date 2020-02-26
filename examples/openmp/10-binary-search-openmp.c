#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_max_threads() 1
#define omp_get_thread_num()  0
#endif

/* ---------------------------------------------------------------------
 * types
 * ------------------------------------------------------------------ */

struct                    node
{
  int                       value;
  struct node*              left;
  struct node*              right;
};

typedef struct node       node_t;

/* ---------------------------------------------------------------------
 * build_tree()
 *
 *   Builds a binary tree. The entries are NOT sorted.
 * ------------------------------------------------------------------ */

node_t*                   build_tree

  ( int                     count )

{
  node_t*  root = NULL;
  int      i;

  if ( count )
  {
    root = (node_t*) calloc ( 1, sizeof(node_t) );

    if ( ! root )
    {
      fprintf ( stderr, "Failed to allocate memory.\n" );
      exit    ( 1 );
    }
  }

  for ( i = 1; i < count; i++ )
  {
    node_t*  node = (node_t*) calloc ( 1, sizeof(node_t) );
    node_t*  top  = root;

    if ( ! node )
    {
      fprintf ( stderr, "Failed to allocate memory.\n" );
      exit    ( 1 );
    }

    node->value = i;

    while ( 1 )
    {
      node_t**  next = NULL;

      if ( rand() % 2 )
      {
        next = &top->left;
      }
      else
      {
        next = &top->right;
      }

      if ( ! (*next) )
      {
        *next = node;
        break;
      }
      else
      {
        top = *next;
      }
    }
  }

  return root;
}

/* ---------------------------------------------------------------------
 * kill_tree()
 *
 *   Destroys a binary tree.
 * ------------------------------------------------------------------ */

void                      kill_tree

  ( node_t*                 root )

{
  if ( root->left )
  {
    kill_tree ( root->left );
  }

  if ( root->right )
  {
    kill_tree ( root->right );
  }

  free ( root );
}

/* ---------------------------------------------------------------------
 * find_value()
 *
 *   Returns a pointer to a node containing a specified value, or
 *   NULL if there is no such node.
 * ------------------------------------------------------------------ */

node_t*                   find_value

  ( node_t*                 root,
    int                     value )

{
  node_t*  node = NULL;

  if ( root )
  {
    if ( root->value == value )
    {
      return root;
    }

    if ( root->right )
    {
      node = find_value ( root->right, value );
    }

    if ( ! node && root->left )
    {
      node = find_value ( root->left,  value );
    }
  }

  return node;
}

/* ---------------------------------------------------------------------
 * main()
 * ------------------------------------------------------------------ */

int main ()
{
  node_t*  root = build_tree ( 100 );

  while ( 1 )
  {
    int  value;

    printf ( "Enter an integer to be found: " );

    if ( scanf( " %d", &value ) == 1 )
    {
      node_t*  node = find_value ( root, value );

      if ( node )
      {
        printf ( "Value found: %d\n", node->value );
      }
      else
      {
        printf ( "Value not found.\n" );
      }
    }
  }

  kill_tree ( root );

  return 0;
}
