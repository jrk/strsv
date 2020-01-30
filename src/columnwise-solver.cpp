#include "cblas.h"
#include "solvers.h"

void columnwise_solver(LowerTriangularEquation &eq) {
    std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());
    int n = eq.n;
    for (int i = 1; i < n; ++i) {
        eq.x[i] -= cblas_sdot(i, &eq.L[i], n, &eq.x[0], 1);
    }
}

REGISTER_SOLVER(columnwise_solver)