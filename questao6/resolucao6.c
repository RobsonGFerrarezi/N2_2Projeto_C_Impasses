#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t fila_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t estat_mutex = PTHREAD_MUTEX_INITIALIZER;

void atualizar_estatisticas() {
    pthread_mutex_lock(&estat_mutex);
    usleep(1000);
    pthread_mutex_unlock(&estat_mutex);
}

void* produtor(void* arg) {

    pthread_mutex_lock(&fila_mutex);

    usleep(1000);

    pthread_mutex_lock(&estat_mutex);

    printf("Produtor executou\n");

    pthread_mutex_unlock(&estat_mutex);
    pthread_mutex_unlock(&fila_mutex);

    return NULL;
}

void* manutencao(void* arg) {

    /* mesma ordem: fila -> estat */
    pthread_mutex_lock(&fila_mutex);

    usleep(1000);

    pthread_mutex_lock(&estat_mutex);

    printf("Manutencao executou\n");

    pthread_mutex_unlock(&estat_mutex);
    pthread_mutex_unlock(&fila_mutex);

    return NULL;
}

int main() {

    pthread_t t1, t2;

    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, manutencao, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}