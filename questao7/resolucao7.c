#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t spooler = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t impressora = PTHREAD_MUTEX_INITIALIZER;

void enviar_para_spooler(const char* usuario) {

    pthread_mutex_lock(&spooler);

    printf("%s enviou documento ao spooler\n", usuario);

    pthread_mutex_lock(&impressora);

    printf("%s imprimindo\n", usuario);

    usleep(1000);

    pthread_mutex_unlock(&impressora);
    pthread_mutex_unlock(&spooler);
}

void* usuario1(void* arg) {
    enviar_para_spooler("usuario1");
    return NULL;
}

void* usuario2(void* arg) {
    enviar_para_spooler("usuario2");
    return NULL;
}

int main() {

    pthread_t t1, t2;

    pthread_create(&t1, NULL, usuario1, NULL);
    pthread_create(&t2, NULL, usuario2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}