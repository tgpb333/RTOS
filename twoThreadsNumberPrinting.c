#include <stdio.h>
#include <pthread.h>

#define MAX_NUM 10
int curr_num = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* print_even(void* arg) {
    while (curr_num <= MAX_NUM) {
        pthread_mutex_lock(&mutex);
        while (curr_num % 2 != 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (curr_num <= MAX_NUM) {
            printf("Even number : %d\n", curr_num);
            curr_num++;
        }

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* print_odd(void* arg) {
    while (curr_num <= MAX_NUM) {
        pthread_mutex_lock(&mutex);
        while (curr_num % 2 == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (curr_num <= MAX_NUM) {
            printf("Odd number : %d\n", curr_num);
            curr_num++;
        }

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t even, odd;
    pthread_create(&even, NULL, print_even, NULL);
    pthread_create(&odd, NULL, print_odd, NULL);

    pthread_join(even, NULL);
    pthread_join(odd, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
