## External projects that need to be fetched
include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

## Project that are likely available locally / have find modules
set(BLAS_TARGETS "")
foreach (BLA_VENDOR IN ITEMS OpenBLAS ATLAS Intel10_64lp_seq Apple Generic)
    find_package(BLAS QUIET)
    if (BLAS_FOUND)
        add_library(blas_${BLA_VENDOR} INTERFACE)
        target_link_libraries(blas_${BLA_VENDOR} INTERFACE ${BLAS_LIBRARIES})
        add_library(BLAS::${BLA_VENDOR} ALIAS blas_${BLA_VENDOR})
        list(APPEND BLAS_TARGETS BLAS::${BLA_VENDOR})
    endif ()
endforeach ()
message(STATUS "Found BLAS targets: ${BLAS_TARGETS}")
