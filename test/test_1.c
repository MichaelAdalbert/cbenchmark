#include <cbenchmark.h>
#include <time.h>
#include <assert.h>

void f() {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 250000000;
    nanosleep(&ts, NULL);
}

int main() {
    int benchmark_result = benchmark(f);
    assert(benchmark_result == NO_ERROR);
    return 0;
}