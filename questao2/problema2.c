#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t r1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t r2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t r3 = PTHREAD_MUTEX_INITIALIZER;

void* t1(void* arg) {
    pthread_mutex_lock(&r1);
    sleep(1);
    pthread_mutex_lock(&r2);
    printf("t1 executou\n");
    pthread_mutex_unlock(&r2);
    pthread_mutex_unlock(&r1);
    return NULL;
}

void* t2(void* arg) {
    pthread_mutex_lock(&r2);
    sleep(1);
    pthread_mutex_lock(&r3);
    printf("t2 executou\n");
    pthread_mutex_unlock(&r3);
    pthread_mutex_unlock(&r2);
    return NULL;
}

void* t3(void* arg) {
    pthread_mutex_lock(&r3);
    sleep(1);
    pthread_mutex_lock(&r1);
    printf("t3 executou\n");
    pthread_mutex_unlock(&r1);
    pthread_mutex_unlock(&r3);
    return NULL;
}

int main() {
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);
    pthread_create(&th3, NULL, t3, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    return 0;
}