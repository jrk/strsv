add_library(solvers SHARED
        LowerTriangularEquation.cpp
        LowerTriangularEquation.h
        blas-solver.cpp
        blocked-solver.cpp
        naive-solver.cpp
        solvers.cpp
        solvers.h
        )

target_link_libraries(solvers
        PRIVATE BLAS::OpenBLAS)
target_include_directories(solvers
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

set(OPT_FLAGS -march=native)
foreach (FLAG IN LISTS OPT_FLAGS)
    check_cxx_compiler_flag("${FLAG}" HAS_FLAG)
    if (HAS_FLAG)
        target_compile_options(solvers PRIVATE "${FLAG}")
    endif ()
endforeach ()