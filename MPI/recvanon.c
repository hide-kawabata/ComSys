#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int myrank, error, tag = 1234, v;
    int buffer[20];
    MPI_Status status;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myrank == 0) {
        fprintf(stderr, "%d: size = %d\n", myrank, size);
        int i;
        for (i = 1; i < size; i++) {
            error = MPI_Recv(&buffer[i], i, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            fprintf(stderr, "%d: received from %d\n", myrank, status.MPI_SOURCE);
        }
        for (i = 1; i < size; i++) {
            fprintf(stderr ,"%d: buffer[%d]=%d\n", myrank, i, buffer[i]);
        }
    } else {
        v = myrank;
        error = MPI_Send(&v, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        fprintf(stderr, "%d: sent %d to %d\n", myrank, v, 0);
    }
    MPI_Finalize();
    return 0;
}
