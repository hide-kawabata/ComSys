#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 1000
int x;
pthread_mutex_t m;

#define MX // perform mutual exclusion

void *func(void *args) {
    usleep(1000);
#ifdef MX
    pthread_mutex_lock(&m);
#endif
    x = x + 1;
#ifdef MX
    pthread_mutex_unlock(&m);
#endif
    return NULL;
}

int main() {
    int i;
    pthread_t pth[N];
    pthread_mutex_init(&m, NULL);
    for (i = 0; i < N; i++) {
        pthread_create(&pth[i], NULL, func, NULL);
    }
    for (i = 0; i < N; i++) {
        pthread_join(pth[i], NULL);
    }
    printf("x = %d\n", x);
    return 0;
}