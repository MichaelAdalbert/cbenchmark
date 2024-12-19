#ifndef CBENCHMARK_H
#define CBENCHMARK_H

enum benchmark_error_e {
    NO_ERROR = 0,
    FUNCTION_NOT_VALID = 1,
    THREAD_KILLED = 2,
    THREAD_NOT_CREATED = 3,
    THREAD_FAILED_TO_JOIN = 4,
};

typedef enum benchmark_error_e benchmark_error_t;

typedef void (*function_t)(void);

benchmark_error_t benchmark(function_t function);

#endif