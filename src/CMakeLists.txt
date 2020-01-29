add_library(solvers SHARED
        blas-solver.cpp
        solvers.cpp
        solvers.h)

target_link_libraries(solvers
        PRIVATE BLAS::OpenBLAS)