#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char**argv)
{


    MPI_Init(&argc,&argv);


    const int N = 16;
    int tag=1;
    int array[N];
    int new_array[N];


    for (int i=0;i<N;i++)
    {
        array[i] = i;
        new_array[i] = 0;
    }
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int loop_length = N/world_size;

    MPI_Request request = MPI_REQUEST_NULL;
    MPI_Status status;
    
    
    if (rank==0)
    {
        MPI_Isend(&array[loop_length -1], 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &request);
        MPI_Irecv(&new_array[0], 1, MPI_INT, world_size-1, tag, MPI_COMM_WORLD, &request);
        for (int i=1; i<loop_length; i++)
        {
            new_array[i] = array[i-1];
        }      
        printf("%d\n", array[loop_length -1]);      
    }

    if ((rank % (world_size-1)) != 0)
    {
        MPI_Isend(&array[(loop_length*(rank + 1))-1], 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD, &request);   
        MPI_Irecv(&new_array[loop_length*rank], 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &request);
        printf("%d\n", new_array[loop_length*rank]);
        for (int i=(rank*loop_length)+1; i<(rank*loop_length)+loop_length; i++)
        {
            new_array[i] = array[i-1];
        }        
    }

    if (rank == world_size-1) 
    {
        MPI_Isend(&array[N-1], 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &request);
        MPI_Irecv(&new_array[loop_length*rank], 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &request);
        
        for (int i=(rank*loop_length)+1; i<(rank*loop_length)+loop_length; i++)
        {
            new_array[i] = array[i-1];
        }     
    }

    MPI_Wait(&request, &status); 

    for (int i=0;i<N;i++)
    {
        printf(" %d ", new_array[i]);
    }
    printf("\n");
    
    MPI_Finalize(); 
    return 0;
    
    
}

