#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t conta1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t conta2 = PTHREAD_MUTEX_INITIALIZER;

void* transferencia_1(void* arg) {
    pthread_mutex_lock(&conta1);
    printf("Thread 1: Bloqueou conta 1...\n");
    sleep(1);
    pthread_mutex_lock(&conta2);
    printf("Transferencia 1 concluida\n");

    pthread_mutex_unlock(&conta2);
    pthread_mutex_unlock(&conta1);
    return NULL;
}

void* transferencia_2(void* arg) {
    pthread_mutex_lock(&conta2);
    printf("Thread 2: Bloqueou conta 2...\n");
    sleep(1);
    pthread_mutex_lock(&conta1);
    printf("Transferencia 2 concluida\n");

    pthread_mutex_unlock(&conta1);
    pthread_mutex_unlock(&conta2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, transferencia_1, NULL);
    pthread_create(&t2, NULL, transferencia_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Fim do programa.\n");
    return 0;
}