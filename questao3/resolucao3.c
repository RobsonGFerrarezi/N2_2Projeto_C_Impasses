#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t banco_mutex = PTHREAD_MUTEX_INITIALIZER;

void registrar_log()
{
    pthread_mutex_lock(&log_mutex);
    usleep(1000);
    pthread_mutex_unlock(&log_mutex);
    printf("Registrar log funcionou!\n");
}

void atualizar_banco()
{
    pthread_mutex_lock(&banco_mutex);
    usleep(1000);
    pthread_mutex_unlock(&banco_mutex);
    printf("Atualizar Banco funcionou!\n");
}

void *thread1(void *arg)
{
    registrar_log();

    atualizar_banco();

    registrar_log();

    return NULL;
}

int main()
{
    pthread_t th1;
    pthread_create(&th1, NULL, thread1, NULL);
    pthread_join(th1, NULL);
    printf("Thread 1 concluiu sem travar!\n");
    return 0;
}