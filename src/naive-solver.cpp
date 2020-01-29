#include "solvers.h"

void naive_solver(LowerTriangularEquation &eq) {
    int n = eq.n;
    for (int i = 0; i < n; ++i) {
        eq.x[i] = eq.b[i];
        for (int j = 0; j < i - 1; ++j) {
            eq.x[i] -= eq.x[j] * eq.L[i + j * n];
        }
    }
}

REGISTER_SOLVER(naive_solver)