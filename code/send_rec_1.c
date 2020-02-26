#include <stdio.h>
#include <mpi.h>

int main ( int argc, char** argv )
{
 int my_rank, proc_count, number;
 MPI_Init(&argc, &argv);
 MPI_Comm_rank ( MPI_COMM_WORLD, &my_rank );
 MPI_Comm_size ( MPI_COMM_WORLD, &proc_count );
 number = 0;
 if (my_rank == 0){
     MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
     MPI_Recv(&number, 1, MPI_INT, proc_count - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
 }
 else if(my_rank < (proc_count-1)){  
     MPI_Recv(&number, 1, MPI_INT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     MPI_Send(&number, 1, MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
     }
 else{
 	MPI_Recv(&number, 1, MPI_INT, my_rank -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
 }
if (my_rank == proc_count){
    printf("%d", proc_count);
}

MPI_Finalize();
return 0;
}
