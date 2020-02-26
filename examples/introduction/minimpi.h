/**
 * mini-MPI wrapper
 */

#include <mpi.h>

/* Ungraceful termination */
void terminate()
{
    fprintf(stderr, "An internal error occured. Terminating!\n");
    MPI_Finalize();
}

/* Initialization */
void init()
{
    if (MPI_Init(NULL, NULL) != MPI_SUCCESS)
    { terminate(); }
}

/* Finalization */
void finalize()
{
    if (MPI_Finalize() != MPI_SUCCESS)
    { terminate(); }
}

/* Get total number of processors */
int get_total_proc_number()
{
    int world_size;
    if (MPI_Comm_size(MPI_COMM_WORLD, &world_size) != MPI_SUCCESS)
        terminate();
    return world_size;
}

/*  Get number of current processor */
int get_my_proc_number()
{
    int world_rank;
    if (MPI_Comm_rank(MPI_COMM_WORLD, &world_rank) != MPI_SUCCESS)
        terminate();
    return world_rank;
}


/* Send an integer to a single process (blocking version) */
void send_int(int value, int dest )
{
    printf("Process %d: Sending an integer to process %d ...\n", get_my_proc_number(), dest);
    if (MPI_Send(&value, 1, MPI_INT, dest, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
        terminate();
}

/* Receive an integer (blocking version) */
void recv_int(int* value, int source )
{
    printf("Process %d: Waiting for an integer...\n", get_my_proc_number());
    if (MPI_Recv(value, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS)
        terminate();
    printf("Process %d: Received one integer.\n", get_my_proc_number());
}
