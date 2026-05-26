#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t cache_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t disco_mutex = PTHREAD_MUTEX_INITIALIZER;

void gravar_disco() {
    usleep(1000);
}

void* atualizar_cache(void* arg) {

    /* ordem global:
       cache -> disco */

    pthread_mutex_lock(&cache_mutex);
    pthread_mutex_lock(&disco_mutex);

    gravar_disco();

    printf("Cache atualizado\n");

    pthread_mutex_unlock(&disco_mutex);
    pthread_mutex_unlock(&cache_mutex);

    return NULL;
}

void* flush_disco_para_cache(void* arg) {

    /* mesma ordem */
    pthread_mutex_lock(&cache_mutex);
    pthread_mutex_lock(&disco_mutex);

    printf("Flush executado\n");

    pthread_mutex_unlock(&disco_mutex);
    pthread_mutex_unlock(&cache_mutex);

    return NULL;
}

int main() {

    pthread_t t1, t2;

    pthread_create(&t1, NULL, atualizar_cache, NULL);
    pthread_create(&t2, NULL, flush_disco_para_cache, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}