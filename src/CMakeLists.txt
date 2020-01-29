add_library(solvers SHARED
        blas-solver.cpp
        solvers.cpp
        solvers.h)

target_link_libraries(solvers
        PRIVATE BLAS::OpenBLAS)
target_include_directories(solvers
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})