#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//#define NUM_THREADS 1
#define NUM_THREADS 11

#define N (1000*1000*1000)

int long m;
pthread_mutex_t m_lock;

void *worker(void *vargp) {
    long int m_local = 0;
    double x, y;
    int i;
    int startidx = *((int*)vargp);
    unsigned int seed = (unsigned int)startidx;
    int c = 0;
    for (i = startidx; i < N; i += NUM_THREADS) {
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
        c++;
    }
    pthread_mutex_lock(&m_lock);
    m += m_local;
    pthread_mutex_unlock(&m_lock);
    return NULL;
}


int main() {
    int i;
    double x, y, pi;
    long int n = (long)N;
    struct timespec ts_start, ts_stop;
    pthread_t tid[NUM_THREADS];
    int args[NUM_THREADS];

    clock_gettime(CLOCK_REALTIME, &ts_start);

    for (i = 0; i < NUM_THREADS; i++) {
        args[i] = i;
        pthread_create(&tid[i], NULL, worker, &args[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    pi = 4.0 * (double)m / (double)n;

    clock_gettime(CLOCK_REALTIME, &ts_stop);
    double t_diff = (ts_stop.tv_sec * (double)1000000000. + ts_stop.tv_nsec)
             - (ts_start.tv_sec * (double)1000000000. + ts_start.tv_nsec);
    printf("n = %ld, m = %ld, pi = %lf\n", n, m, pi);
    printf("total time: %10lf, nth=%d\n", t_diff / 1000000000., NUM_THREADS);

    return 0;
}
