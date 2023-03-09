#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NO_OF_THREADS 2
#define MAX_NO_OF_ELEMENTS 100000000

typedef struct arg_data {
    int thread_number;
} arg_data;

static int arr[MAX_NO_OF_ELEMENTS];

static long long int sum;

void* worker_sum(void* arg) {
    arg_data* current_thread_data = (arg_data*)arg;

    printf("Current thread no is: %d\n", current_thread_data->thread_number);

    // Determine the bounds
    int startpart = (current_thread_data->thread_number) * (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);
    int endpart = (current_thread_data->thread_number + 1) * (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);

    printf("Here will be the sum %d to %d\n", arr[startpart], arr[endpart - 1]);

    long long int current_thread_sum = 0;

    for(int i=startpart; i<endpart; i++) {
        current_thread_sum += arr[i];
    }

    sum += current_thread_sum;

    return NULL;
}

int main() {
    // let the array consist of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for(int i=0; i<MAX_NO_OF_ELEMENTS; i++) {
        arr[i] = i + 1;
    }

    // pthread objects
    pthread_t id[MAX_NO_OF_THREADS];

    // argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];

    // total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d number of threads...\n", no_of_threads);

    // setup timing
    clock_t start, end;
    double cpu_time_taken;

    start = clock();
	
	int thread_no = 0;

    // creating the child thread
    for(int i=0; i<MAX_NO_OF_THREADS; i++) {
        arg_arr[i].thread_number = thread_no;
        pthread_create(&id[i], NULL, worker_sum, &arg_arr[i]);
        thread_no++;
    }
	
    // joining
    for(int i=0; i<MAX_NO_OF_THREADS; i++) {
        pthread_join(id[i], NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("All child threads have finished their works...\n");
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);

    return 0;
}