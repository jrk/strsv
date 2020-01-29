add_executable(benchmark_strsv)

target_sources(benchmark_strsv PRIVATE benchmark_strsv.cpp)
target_link_libraries(benchmark_strsv
        PRIVATE
        benchmark::benchmark
        solvers)