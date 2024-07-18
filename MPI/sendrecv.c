#include <stdio.h>
#include <mpi.h>

// number of processes : 2

int main(int argc, char **argv) {
    int myrank, error, tag = 1234, tag2 = 1234; //tag2 = 6789;
    int sbuf, rbuf;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0) {
        sbuf = 1;
        rbuf = 2;
        MPI_Sendrecv(&sbuf, 1, MPI_INT, 1, tag, &rbuf, 1, MPI_INT, 1, tag2, MPI_COMM_WORLD, &status);
        fprintf(stderr, "%d: sbuf = %d, rbuf = %d\n", myrank, sbuf, rbuf);
    } else {
        sbuf = 3;
        rbuf = 4;
        MPI_Sendrecv(&sbuf, 1, MPI_INT, 0, tag2, &rbuf, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        fprintf(stderr, "%d: sbuf = %d, rbuf = %d\n", myrank, sbuf, rbuf);
    }
    MPI_Finalize();
    return 0;
}
