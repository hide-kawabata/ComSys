#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NTH 10

void *thread(void *vargp) {
    usleep(1000);
    printf("Hello, world! (%d)\n", *(int*)vargp);
    return NULL;
}

int main() {
    int i;
    pthread_t tid[NTH];
    int arg[NTH];
    printf("I'm the main thread.\n");
    for (i = 0; i < NTH; i++) {
        arg[i] = i * 100;
        pthread_create(&tid[i], NULL, thread, &arg[i]);
    }
    for (i = 0; i < NTH; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("Bye!\n");
    return 0;
}
