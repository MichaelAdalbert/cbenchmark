cmake_minimum_required(VERSION 3.30)
project(cbenchmark C)

set(CMAKE_C_STANDARD 17)

find_package(Threads REQUIRED)

add_library(cbenchmark STATIC lib/cbenchmark.c)

target_link_libraries(cbenchmark PRIVATE Threads::Threads)

target_include_directories(cbenchmark PUBLIC include)

enable_testing()

add_executable(test_1 test/test_1.c)

target_link_libraries(test_1 PRIVATE cbenchmark Threads::Threads)

add_test(NAME "test-1" COMMAND test_1)

add_executable(test_2 test/test_2.c)

target_link_libraries(test_2 PRIVATE cbenchmark Threads::Threads)

add_test(NAME "test-2" COMMAND test_2)