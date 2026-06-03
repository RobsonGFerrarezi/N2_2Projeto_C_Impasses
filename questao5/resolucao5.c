#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void processar(int nivel)
{
    if (nivel == 0)
        return;

    pthread_mutex_lock(&A);
    usleep(1000);

    if (nivel % 2 == 0)
    {
        pthread_mutex_lock(&B);
        pthread_mutex_unlock(&B);
    }

    pthread_mutex_unlock(&A);

    processar(nivel - 1);
}

void *thread1(void *arg)
{
    processar(2);
    printf("thread 1 executada!\n");
    return NULL;
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&A);
    pthread_mutex_lock(&B);
    usleep(1000);
    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    printf("thread 2 executada!\n");
    return NULL;
}

int main()
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, thread1, NULL);
    pthread_create(&th2, NULL, thread2, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Programa executou com sucesso e sem travamentos!\n");
    return 0;
}