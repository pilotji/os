
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5
#define ITEMS 10

// ==========================================
// PART 1: THREAD SYNCHRONIZATION
// ==========================================

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

void threadSync() {
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

    printf("\nFinal counter = %d\n", count);

    sem_destroy(&s);
    pthread_mutex_destroy(&m);
}


// ==========================================
// PART 2: PRODUCER-CONSUMER PROBLEM
// ==========================================

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 1; i <= ITEMS; i++) {

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = i;

        printf("Producer produced item %d at position %d\n",
               i, in);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg) {
    int item;

    for (int i = 1; i <= ITEMS; i++) {

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed item %d from position %d\n",
               item, out);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }

    return NULL;
}

void producerConsumer() {
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);
}


// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {
    int ch;

    printf("\n========== MENU ==========\n");
    printf("1. Thread Synchronization\n");
    printf("2. Producer-Consumer Problem\n");
    printf("==========================\n");

    printf("Enter your choice: ");

    if (scanf("%d", &ch) != 1 || ch < 1 || ch > 2) {
        printf("Invalid choice!\n");
        return 1;
    }

    switch (ch) {

        case 1:
            printf("\n--- THREAD SYNCHRONIZATION ---\n");
            threadSync();
            break;

        case 2:
            printf("\n--- PRODUCER-CONSUMER PROBLEM ---\n");
            producerConsumer();
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
