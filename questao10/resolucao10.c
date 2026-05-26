#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t c = PTHREAD_MUTEX_INITIALIZER;

void* t1(void* arg) {

    pthread_mutex_lock(&a);
    pthread_mutex_lock(&b);
    pthread_mutex_lock(&c);

    printf("t1 executou\n");

    pthread_mutex_unlock(&c);
    pthread_mutex_unlock(&b);
    pthread_mutex_unlock(&a);

    return NULL;
}

void* t2(void* arg) {

    /* mesma ordem global */
    pthread_mutex_lock(&a);
    pthread_mutex_lock(&b);
    pthread_mutex_lock(&c);

    printf("t2 executou\n");

    pthread_mutex_unlock(&c);
    pthread_mutex_unlock(&b);
    pthread_mutex_unlock(&a);

    return NULL;
}

void* t3(void* arg) {

    /* mesma ordem global */
    pthread_mutex_lock(&a);
    pthread_mutex_lock(&b);

    printf("t3 executou\n");

    pthread_mutex_unlock(&b);
    pthread_mutex_unlock(&a);

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