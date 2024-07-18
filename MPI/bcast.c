#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int myrank, v = -1;
    int root = 0;
    MPI_Status status;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myrank == 0) {
        v = 8;
        MPI_Bcast(&v, 1, MPI_INT, root, MPI_COMM_WORLD);
        fprintf(stderr, "%d: sent %d\n", myrank, v);
    } else {
        MPI_Bcast(&v, 1, MPI_INT, root, MPI_COMM_WORLD);
        fprintf(stderr, "%d: recieved %d\n", myrank, v);
    }
    MPI_Finalize();
    return 0;
}
