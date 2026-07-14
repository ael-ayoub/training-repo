#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int shared_counter = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        shared_counter++;
        pthread_mutex_unlock(&lock);
    }
    printf("worker %d finished\n", id);
    return NULL;
}

int main(void) {
    const int n_threads = 4;
    pthread_t threads[n_threads];
    int ids[n_threads];

    for (int i = 0; i < n_threads; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            fprintf(stderr, "failed to spawn thread %d\n", i);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("final counter: %d\n", shared_counter);
    pthread_mutex_destroy(&lock);
    return EXIT_SUCCESS;
}
