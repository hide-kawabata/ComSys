#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define INTERVAL (1000*1000*10)

int main() {
    int i;
    double x, area, pi, interval;
    long int n_intervals = (long)INTERVAL;
    double m = 0.0;
    struct timespec ts_start, ts_stop;
    srand(0);
    int tid;

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

    double m_local = 0.0;
#pragma omp parallel private(m_local, interval, x, area)
    {
        m_local = 0;
        interval = 1.0 / n_intervals;
#pragma omp for
        for (i = 0; i < n_intervals; i++) {
            x = interval * (double)i;
            area = interval * (double)sqrt(1.0 - x*x);
            m_local = m_local + area;
        }
#pragma omp atomic
        m += m_local;
    }
    pi = 4.0 * (double)m;

    clock_gettime(CLOCK_REALTIME, &ts_stop);
    double t_diff = (ts_stop.tv_sec * (double)1000000000. + ts_stop.tv_nsec)
             - (ts_start.tv_sec * (double)1000000000. + ts_start.tv_nsec);
    printf("n_interval = %ld, m = %lf, pi = %lf\n", n_intervals, m, pi);
    printf("total time:    %10lf\n", t_diff / 1000000000.);
    
    return 0;
}