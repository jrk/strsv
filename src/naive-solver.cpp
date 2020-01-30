#ifdef NAIVE_SOLVER_USE_BLAS
#include <cblas.h>
#endif

#include "solvers.h"

void naive_solver(LowerTriangularEquation &eq) {
    // These two implementations perform the same.
#ifdef NAIVE_SOLVER_USE_BLAS
    std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());
    int n = eq.n;
    for (int i = 1; i < n; ++i) {
        eq.x[i] -= cblas_sdot(i, &eq.L[i], n, &eq.x[0], 1);
    }
#else
    int n = eq.n;
    for (int i = 0; i < n; ++i) {
        eq.x[i] = eq.b[i];
        for (int j = 0; j < i; ++j) {
            eq.x[i] -= eq.x[j] * eq.L[i + j * n];
        }
    }
#endif
}

REGISTER_SOLVER(naive_solver)