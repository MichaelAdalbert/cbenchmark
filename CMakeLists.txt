cmake_minimum_required(VERSION 3.30)
project(cbenchmark C)

set(CMAKE_C_STANDARD 17)

find_package(Threads REQUIRED)

add_library(cbenchmark STATIC lib/cbenchmark.c)

target_link_libraries(cbenchmark PRIVATE Threads::Threads)
target_include_directories(cbenchmark PUBLIC include)
if (CMAKE_BUILD_TYPE MATCHES "Debug" )
    target_compile_options(cbenchmark PRIVATE -Og -g3 -Wall -Wextra -Werror)
elseif ()
    target_compile_options(cbenchmark PRIVATE -O2 -flto)
    target_link_options(cbenchmark PRIVATE -flto)
endif ()

include(cmake/test.cmake)
