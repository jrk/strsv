cmake_minimum_required(VERSION 3.14)

## External projects that need to be fetched
include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark

# Hack around googlebenchmark's old CMake policy set by creating an option here instead of simply set()-ing.
# This prevents googlebenchmark from injecting its own tests into the build.
# See CMP0077.
option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

## Projects that are likely available locally / have find modules
set(BLAS_TARGETS "")
set(BLAS_VENDORS Intel10_64lp_seq OpenBLAS Apple Generic)
foreach (BLA_VENDOR IN LISTS BLAS_VENDORS)
    find_package(BLAS QUIET)
    if (BLAS_FOUND)
        add_library(blas_${BLA_VENDOR} INTERFACE)
        target_link_libraries(blas_${BLA_VENDOR} INTERFACE ${BLAS_LIBRARIES})
        target_compile_definitions(blas_${BLA_VENDOR} INTERFACE BLA_VENDOR_${BLA_VENDOR})

        add_library(BLAS::${BLA_VENDOR} ALIAS blas_${BLA_VENDOR})
        list(APPEND BLAS_TARGETS BLAS::${BLA_VENDOR})

        if (NOT TARGET BLAS::BLAS)
            add_library(BLAS::BLAS ALIAS blas_${BLA_VENDOR})
        endif ()
    endif ()
endforeach ()
message(STATUS "Found BLAS targets: ${BLAS_TARGETS}")

