enable_testing()

file(GLOB TESTS test/*)
foreach (TEST_FILE ${TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE cbenchmark Threads::Threads)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    if (CMAKE_BUILD_TYPE MATCHES "Debug" )
        target_compile_options(${TEST_NAME} PRIVATE -Og -g3 -Wall -Wextra -Werror)
    elseif ()
        target_compile_options(${TEST_NAME} PRIVATE -O2 -flto)
        target_link_options(${TEST_NAME} PRIVATE -flto)
    endif ()

endforeach ()