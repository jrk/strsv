#include "cblas.h"
#include "solvers.h"

void blas_solver(float *L, float *x, float *b, int n) {
    std::copy(b, b + n, x);
    cblas_strsv(CblasColMajor,
                CblasLower,
                CblasNoTrans,
                CblasUnit,
                n, L, n, x,
                1);
}

REGISTER_SOLVER(blas_solver)