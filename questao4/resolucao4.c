#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *arg)
{
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);

    printf("t1 executando\n");

    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return NULL;
}

void *t2(void *arg)
{
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);

    printf("t2 executando\n");

    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return NULL;
}

int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Executado com sucesso!\n");
    return 0;
}