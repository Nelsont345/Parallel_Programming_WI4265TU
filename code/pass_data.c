#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc,&argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = 4;
    if(rank == 0)
    {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, world_size-1,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("final val %d\n", data);
    }
    if((rank % (world_size-1)) != 0)
    {
        MPI_Recv(&data, 1, MPI_INT, rank-1,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        data = data*4;
        MPI_Send(&data, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&data, 1, MPI_INT, world_size-2,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        data = data*4;
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
   

    MPI_Finalize();
    return 0;
}

    
    