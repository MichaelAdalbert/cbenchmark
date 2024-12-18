#include "cbenchmark.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

struct benchmark_data_s {
    function_t function;
    bool finished;
    bool benchmark_ended;
    uint64_t iterations;
};

typedef struct benchmark_data_s benchmark_data_t;

static benchmark_data_t init_benchmark_data(function_t function) {
    benchmark_data_t benchmark_data;
    benchmark_data.function = function;
    benchmark_data.benchmark_ended = false;
    benchmark_data.finished = false;
    benchmark_data.iterations = 0;
    return benchmark_data;
}

static void* benchmark_function(void *arg) {
    benchmark_data_t* benchmark_data = arg;
    while (benchmark_data->finished == false) {
        benchmark_data->function();
        benchmark_data->iterations++;
    }
    benchmark_data->benchmark_ended = true;
    return NULL;
}

int benchmark(const function_t function) {
    benchmark_data_t benchmark_data = init_benchmark_data(function);
    pthread_t thread;
    int result = 0;

    const int pthread_creation = pthread_create(&thread, NULL, benchmark_function, &benchmark_data);
    if (pthread_creation != 0) {
        perror("pthread_create");
        return 1;
    }

    sleep(1);

    benchmark_data.finished = true;

    sleep(1);

    if (benchmark_data.benchmark_ended) {
        const int pthread_joined = pthread_join(thread, NULL);
        if (pthread_joined != 0) {
            perror("pthread_join");
        }
    } else {
        const int pthread_canceled = pthread_cancel(thread);
        if (pthread_canceled != 0) {
            perror("pthread_cancel");
        }
        result = 2;
    }

    printf("Benchmark iterations: %llu\n", benchmark_data.iterations);
    return result;
}