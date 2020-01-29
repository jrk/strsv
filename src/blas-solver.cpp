#include <cstring>
#include "cblas.h"
#include "solvers.h"

void blas_solver(float *L, float *x, float *b, int n) {
    memcpy(x, b, sizeof(*x) * n);
    cblas_strsv(CblasColMajor,
                CblasLower,
                CblasNoTrans,
                CblasUnit,
                n, L, n, x,
                1);
}

REGISTER_SOLVER(blas_solver)