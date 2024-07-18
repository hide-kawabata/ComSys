#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int myrank, buf[3] = {-1, -1, -1}, tag = 1234;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0) {
        buf[0] = 1;
        buf[1] = 2;
        buf[2] = 3;
        int i;
        for (i = 0; i < 3; i++) {
            fprintf(stderr ,"%d: buf[i]=%d\n", myrank, buf[i]);
        }
        MPI_Send(buf, 2, MPI_INT, 1, tag, MPI_COMM_WORLD);
        fprintf(stderr, "%d: sent to %d\n", myrank, 1);
    } else if (myrank == 1) {
        MPI_Recv(&buf[1], 2, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        fprintf(stderr, "%d: received from %d\n", myrank, 1);
        int i;
        for (i = 0; i < 3; i++) {
            fprintf(stderr ,"%d: buf[i]=%d\n", myrank, buf[i]);
        }
    } else {
        fprintf(stdout, "%d: I am free.\n", myrank);
    }
    MPI_Finalize();
    return 0;
}
