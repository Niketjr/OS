#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (pid + N - 1) % N
#define RIGHT (pid + 1) % N

pthread_mutex_t mutex;
pthread_cond_t condition[N];
int state[N];

void *philosopher(void *arg) {
    int pid = *((int *) arg);

    while (1) {
        printf("Philosopher %d is thinking.\n", pid);

        // Simulate thinking
        sleep(rand() % 5);

        pthread_mutex_lock(&mutex);
        state[pid] = HUNGRY;
        printf("Philosopher %d is hungry.\n", pid);
        // Try to acquire forks
        while (state[LEFT] == EATING || state[RIGHT] == EATING) {
            pthread_cond_wait(&condition[pid], &mutex);
        }
        // Acquired forks
        state[pid] = EATING;
        printf("Philosopher %d is eating.\n", pid);
        pthread_mutex_unlock(&mutex);

        // Simulate eating
        sleep(rand() % 5);

        pthread_mutex_lock(&mutex);
        // Finished eating
        state[pid] = THINKING;
        printf("Philosopher %d finished eating and is thinking.\n", pid);

        // Signal neighbors
        pthread_cond_signal(&condition[LEFT]);
        pthread_cond_signal(&condition[RIGHT]);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N; ++i) {
        pthread_cond_init(&condition[i], NULL);
    }

    for (int i = 0; i < N; ++i) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    for (int i = 0; i < N; ++i) {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}
