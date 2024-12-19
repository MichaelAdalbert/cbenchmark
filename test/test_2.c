#include <cbenchmark.h>
#include <time.h>
#include <assert.h>

void f() {
    struct timespec ts;
    ts.tv_sec = 3;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);
}

int main() {
    int benchmark_result = benchmark(f);
    assert(benchmark_result == THREAD_KILLED);
    return 0;
}