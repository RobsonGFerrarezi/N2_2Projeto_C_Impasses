#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void* t1(void* arg) {
    while (1) {
        pthread_mutex_lock(&m1);
        if (pthread_mutex_trylock(&m2) == 0) {
            break;
        }
        pthread_mutex_unlock(&m1);
        usleep(100);
    }
    printf("t1 executando\n");
    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return NULL;
}

void* t2(void* arg) {
    while (1) {
        pthread_mutex_lock(&m2);
        if (pthread_mutex_trylock(&m1) == 0) {
            break;
        }
        pthread_mutex_unlock(&m2);
        usleep(100);
    }
    printf("t2 executando\n");
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
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