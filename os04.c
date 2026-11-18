
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room; 
sem_t forks[5];

void *philosopher(void *arg) {
    int i = *(int *)arg;

    printf("Philosopher %d is thinking.\n", i + 1);

    sem_wait(&room);
    sem_wait(&forks[i]);
    sem_wait(&forks[(i + 1) % 5]);

    printf("Philosopher %d picked up both forks and is eating.\n", i + 1);
    sleep(1);

    sem_post(&forks[(i + 1) % 5]);
    sem_post(&forks[i]);
    sem_post(&room);

    printf("Philosopher %d finished eating and released both forks.\n", i + 1);
    return NULL;
}

int main() {
    pthread_t t[5];
    int id[5];

    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++) {
        sem_init(&forks[i], 0, 1);
        id[i] = i;
    }

    for (int i = 0; i < 5; i++)
        pthread_create(&t[i], NULL, philosopher, &id[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    for (int i = 0; i < 5; i++)
        sem_destroy(&forks[i]);

    sem_destroy(&room);
    return 0;
}
