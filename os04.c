
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;
pthread_mutex_t m;
int count = 0;

void *worker(void *arg) {
    int id = *(int *)arg;

    sem_wait(&s);
    printf("Thread %d entered (semaphore acquired)\n", id);

    pthread_mutex_lock(&m);
    printf("Thread %d: Counter = %d\n", id, ++count);
    pthread_mutex_unlock(&m);

    sleep(1);
    printf("Thread %d leaving (semaphore released)\n", id);
    sem_post(&s);

    return NULL;
}

int main() {
    pthread_t t[5];
    int id[5];

    sem_init(&s, 0, 2);
    pthread_mutex_init(&m, NULL);

    for (int i = 0; i < 5; i++) {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, worker, &id[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    printf("Final counter = %d\n", count);

    sem_destroy(&s);
    pthread_mutex_destroy(&m);

    return 0;
}
