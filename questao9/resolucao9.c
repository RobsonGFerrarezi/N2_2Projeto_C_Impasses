#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t y = PTHREAD_MUTEX_INITIALIZER;

void* t1(void* arg) {

    pthread_mutex_lock(&x);
    pthread_mutex_lock(&y);

    printf("t1 concluiu\n");

    pthread_mutex_unlock(&y);
    pthread_mutex_unlock(&x);

    return NULL;
}

void* t2(void* arg) {

    /* mesma ordem */
    pthread_mutex_lock(&x);
    pthread_mutex_lock(&y);

    printf("t2 concluiu\n");

    pthread_mutex_unlock(&y);
    pthread_mutex_unlock(&x);

    return NULL;
}

int main() {

    pthread_t th1, th2;

    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}