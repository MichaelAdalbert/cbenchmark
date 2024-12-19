#include <cbenchmark.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    int benchmark_result = benchmark(NULL);
    assert(benchmark_result == FUNCTION_NOT_VALID);
    return 0;
}