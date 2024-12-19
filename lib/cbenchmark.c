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

static benchmark_error_t init_benchmark_data(benchmark_data_t *benchmark_data, const function_t function) {
    if (NULL == function) {
        return FUNCTION_NOT_VALID;
    }
    benchmark_data->function = function;
    benchmark_data->benchmark_ended = false;
    benchmark_data->finished = false;
    benchmark_data->iterations = 0;
    return NO_ERROR;
}

static void *benchmark_function(void *arg) {
    benchmark_data_t *benchmark_data = arg;
    while (benchmark_data->finished == false) {
        benchmark_data->function();
        benchmark_data->iterations++;
    }
    benchmark_data->benchmark_ended = true;
    return NULL;
}

benchmark_error_t benchmark(const function_t function) {
    benchmark_data_t benchmark_data;
    pthread_t thread;
    benchmark_error_t err;

    if ((err = init_benchmark_data(&benchmark_data, function)) != 0) {
        fprintf(stderr, "Failed to initialize benchmark data\n");
        return err;
    }

    if (pthread_create(&thread, NULL, benchmark_function, &benchmark_data) != 0) {
        perror("pthread_create");
        return THREAD_NOT_CREATED;
    }

    sleep(1);

    benchmark_data.finished = true;

    sleep(1);

    if (!benchmark_data.benchmark_ended) {
        if (pthread_cancel(thread) != 0) {
            perror("pthread_cancel");
        }
        return THREAD_KILLED;
    }

    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return THREAD_FAILED_TO_JOIN;
    }

    printf("Benchmark iterations: %llu\n", benchmark_data.iterations);
    return NO_ERROR;
}
