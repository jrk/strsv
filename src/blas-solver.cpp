#include <cblas.h>
#include "solvers.h"

void blas_solver(LowerTriangularEquation &eq) {
    std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());
    cblas_strsv(CblasColMajor,
                CblasLower,
                CblasNoTrans,
                CblasUnit,
                eq.n, eq.L.data(), eq.n, eq.x.data(),
                1);
}

REGISTER_SOLVER(blas_solver)