#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (1000*1000*1000)

int main() {
    int i;
    double x, y, pi;
    long int n = (long)N;
    long int m = 0;
    struct timespec ts_start, ts_stop;
    srand(0);

    clock_gettime(CLOCK_REALTIME, &ts_start);

    long int m_local = 0;
    for (i = 0; i < n; i++) {
        x = ((double)rand()) / ((double)RAND_MAX);
        y = ((double)rand()) / ((double)RAND_MAX);
        if (x*x + y*y <= 1.0) {
            m += 1;
        }
    }
    pi = 4.0 * (double)m / (double)n;

    clock_gettime(CLOCK_REALTIME, &ts_stop);
    
    double t_diff = (ts_stop.tv_sec * (double)1000000000. + ts_stop.tv_nsec)
             - (ts_start.tv_sec * (double)1000000000. + ts_start.tv_nsec);
    printf("n = %ld, m = %ld, pi = %lf\n", n, m, pi);
    printf("total time:    %10lf\n", t_diff / 1000000000.);

    return 0;
}