add_executable(benchmark_strsv benchmark_strsv.cpp)
target_link_libraries(benchmark_strsv
        PRIVATE
        benchmark::benchmark
        solvers)

include(GoogleTest)
add_executable(correctness_strsv correctness_strsv.cpp)
target_link_libraries(correctness_strsv
        PRIVATE
        solvers
        gtest_main)
gtest_add_tests(TARGET correctness_strsv)