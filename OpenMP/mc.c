#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N (1000*1000*1000)

int main() {
    int i;
    double x, y, pi;
    long int n = (long)N;
    long int m = 0;
    struct timespec ts_start, ts_stop;
    srand(0);
    int tid;
    unsigned int seed;
/*
  You can control the number of threads as follows:
  $ env OMP_NUM_THREADS=4 ./mc
*/
// or set the number statically as follows:
//    omp_set_num_threads(1);
//    omp_set_num_threads(20);
//    omp_set_num_threads(100);
#pragma omp parallel private (tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            int nth = omp_get_num_threads();
            printf("number of threads = %d\n", nth);
            int nproc = omp_get_num_procs();
            printf("number of processors = %d\n", nproc);
        }
    }

    clock_gettime(CLOCK_REALTIME, &ts_start);

    long int m_local = 0;
#pragma omp parallel private(m_local, x, y)
    {
        unsigned int seed = omp_get_thread_num();
        m_local = 0;
#pragma omp for
        for (i = 0; i < n; i++) {
#if 0
            x = ((double)rand()) / ((double)RAND_MAX);
            y = ((double)rand()) / ((double)RAND_MAX);
#else
            x = ((double)rand_r(&seed)) / ((double)RAND_MAX);
            y = ((double)rand_r(&seed)) / ((double)RAND_MAX);
#endif
            if (x*x + y*y <= 1.0) {
                m_local += 1;
            }
        }
#pragma omp atomic
        m += m_local;
    }
    pi = 4.0 * (double)m / (double)n;

    clock_gettime(CLOCK_REALTIME, &ts_stop);
    double t_diff = (ts_stop.tv_sec * (double)1000000000. + ts_stop.tv_nsec)
             - (ts_start.tv_sec * (double)1000000000. + ts_start.tv_nsec);
    printf("n = %ld, m = %ld, pi = %lf\n", n, m, pi);
    printf("total time:    %10lf\n", t_diff / 1000000000.);

    return 0;
}
