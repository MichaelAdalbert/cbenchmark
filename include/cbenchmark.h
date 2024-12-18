#ifndef CBENCHMARK_H
#define CBENCHMARK_H

typedef void (*function_t)(void);

int benchmark(function_t function);

#endif