#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 4

void *thread(void *vargp) {
  int myid = *((int *)vargp); 
  printf("Hello from thread %d\n", myid); 
  return NULL; 
}

int main() {
  pthread_t tid[N];
  int i, *ptr;
  for (i=0;i<N;i++) {
//    ptr = malloc(sizeof(int));
//    *ptr = i;
//    pthread_create(&tid[i], NULL, thread, ptr); 
    pthread_create(&tid[i], NULL, thread, &i);
  }
  for (i=0;i<N;i++) {
    pthread_join(tid[i], NULL); 
  }
  return 0;
}
