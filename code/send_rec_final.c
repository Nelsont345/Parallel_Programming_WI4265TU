#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char**argv)
{


    MPI_Init(&argc,&argv);


    const int N = 20;
    int *array[N];
    int *new_array[N];
    for (int i=0;i<N;i++)
    {
        array[i] = malloc(sizeof(int));
        new_array[i] = malloc(sizeof(int));
    }


    for (int i=0;i<N;i++)
    {
        *array[i] = i;
        *new_array[i] = 0;
    }
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int loop_length = N/world_size;

    
    /*MPI_Request  *reqs[2*N];
    
    for (int i=0;i<2*N;i++)
    {
        reqs[i]= malloc(sizeof(int));
    }
    */
    MPI_Request request = MPI_REQUEST_NULL;
    
    
    if (rank==0)
    {
        MPI_Irecv(&new_array[0], 1, MPI_INT, world_size-1, 11, MPI_COMM_WORLD, &request);
        
        for (int i=1; i<loop_length; i++)
        {
            *new_array[i] = *array[i-1];
        }
        
        MPI_Isend(&array[loop_length -1], 1, MPI_INT, 1, 11, MPI_COMM_WORLD, &request);

        //MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); 
    }
    if ((rank % (world_size-1)) != 0)
    {
        MPI_Irecv(&new_array[rank*loop_length], 1, MPI_INT, rank-1, 11, MPI_COMM_WORLD, &request);
        
        for (int i=rank*loop_length; i<(rank*loop_length)+loop_length-1; i++)
        {
            *new_array[i] = *array[i-1];
        }
        
        MPI_Isend(&array[loop_length*rank + 1], 1, MPI_INT, rank+1, 11, MPI_COMM_WORLD, &request);   
    }

    if (rank == world_size-1) 
    {
        //MPI_Irecv(&new_array[-1], 1, MPI_INT, rank-1, 11, MPI_COMM_WORLD, &request);
        
        for (int i=rank*loop_length; i<(rank*loop_length)+loop_length-1; i++)
        {
            *new_array[i] = *array[i-1];
        }
        
        //MPI_Isend(&array[N-1], 1, MPI_INT, 0, 11, MPI_COMM_WORLD, &request);
        
    }
    if (rank != 5) //Can't print first digits for rank=0
    {
        for (int i=0;i<N;i++)
        {
            printf(" %d ", *new_array[i]);
        }
        printf("\n");
    }
    else
    {   
        for (int i=1;i<16;i++)
        {
            printf("rank 1:%d, %d \n", 16-i, *new_array[N-i]);
        }

    }
    MPI_Finalize();

    
    return 0;
    
    
}

