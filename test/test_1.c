#include <cbenchmark.h>
#include <time.h>
#include <assert.h>

void f() {
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
}

int main() {
    int benchmark_result = benchmark(f);
    assert(benchmark_result == 0);
    return 0;
}