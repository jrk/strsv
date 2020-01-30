#include <cstring>
#include "solvers.h"

typedef float v4sf __attribute__ ((vector_size (16), aligned(1)));

// TODO: for now, assumes n%4=0
void blocked_solver(LowerTriangularEquation &eq) {
    int n = eq.n;

    std::memset(eq.x.data(), 0, n * sizeof(float));

    for (int block = 0; block < n / 4; ++block) {
        int lowJ = 4 * block;
        int lowI = 4 * block;

        for (int j = 0; j < 4; ++j) {
            int L_j = lowJ + j;
            eq.x[L_j] += eq.b[L_j];
            for (int i = j + 1; i < 4; ++i) {
                int L_i = lowI + i;
                eq.x[L_i] -= eq.x[L_j] * eq.L[L_i + n * L_j];
            }
        }

        v4sf x_j0 = {eq.x[lowJ], eq.x[lowJ], eq.x[lowJ], eq.x[lowJ]};
        v4sf x_j1 = {eq.x[lowJ + 1], eq.x[lowJ + 1], eq.x[lowJ + 1], eq.x[lowJ + 1]};
        v4sf x_j2 = {eq.x[lowJ + 2], eq.x[lowJ + 2], eq.x[lowJ + 2], eq.x[lowJ + 2]};
        v4sf x_j3 = {eq.x[lowJ + 3], eq.x[lowJ + 3], eq.x[lowJ + 3], eq.x[lowJ + 3]};
        for (int square = block + 1; square < n / 4; ++square) {
            int sqLowI = lowI + 4 * square;
            v4sf x_i = *(v4sf *) (&eq.x[sqLowI]);

            v4sf L_0 = *(v4sf *) (&eq.L[sqLowI + n * lowJ]);
            v4sf L_1 = *(v4sf *) (&eq.L[sqLowI + n * (lowJ + 1)]);
            v4sf L_2 = *(v4sf *) (&eq.L[sqLowI + n * (lowJ + 2)]);
            v4sf L_3 = *(v4sf *) (&eq.L[sqLowI + n * (lowJ + 3)]);

            x_i -= x_j0 * L_0 +
                   x_j1 * L_1 +
                   x_j2 * L_2 +
                   x_j3 * L_3;

            *(v4sf *) (&eq.x[sqLowI]) = x_i;
        }
    }
}

REGISTER_SOLVER(blocked_solver)