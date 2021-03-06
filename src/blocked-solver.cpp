#include "solvers.h"

typedef float v4sf __attribute__((vector_size(16), aligned(1)));

// TODO: for simplicity, assumes n%4=0
void blocked_solver(LowerTriangularEquation &eq) {
  int n = eq.n;

  std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());

  for (int bkLowJ = 0; bkLowJ < n; bkLowJ += 4) {

    int trLowI = bkLowJ;
    for (int j = 0; j < 4; ++j) {
      int L_j = bkLowJ + j;
      for (int i = j + 1; i < 4; ++i) {
        int L_i = trLowI + i;
        eq.x[L_i] -= eq.x[L_j] * eq.L[L_i + n * L_j];
      }
    }

    v4sf x_j0 = {eq.x[bkLowJ], eq.x[bkLowJ], eq.x[bkLowJ], eq.x[bkLowJ]};
    v4sf x_j1 = {eq.x[bkLowJ + 1], eq.x[bkLowJ + 1], eq.x[bkLowJ + 1],
                 eq.x[bkLowJ + 1]};
    v4sf x_j2 = {eq.x[bkLowJ + 2], eq.x[bkLowJ + 2], eq.x[bkLowJ + 2],
                 eq.x[bkLowJ + 2]};
    v4sf x_j3 = {eq.x[bkLowJ + 3], eq.x[bkLowJ + 3], eq.x[bkLowJ + 3],
                 eq.x[bkLowJ + 3]};

    for (int sqLowI = bkLowJ + 4; sqLowI < n; sqLowI += 4) {
      v4sf x_i = *(v4sf *)(&eq.x[sqLowI]);

      v4sf L_0 = *(v4sf *)(&eq.L[sqLowI + n * bkLowJ]);
      v4sf L_1 = *(v4sf *)(&eq.L[sqLowI + n * (bkLowJ + 1)]);
      v4sf L_2 = *(v4sf *)(&eq.L[sqLowI + n * (bkLowJ + 2)]);
      v4sf L_3 = *(v4sf *)(&eq.L[sqLowI + n * (bkLowJ + 3)]);

      x_i -= x_j0 * L_0 + x_j1 * L_1 + x_j2 * L_2 + x_j3 * L_3;

      *(v4sf *)(&eq.x[sqLowI]) = x_i;
    }
  }
}

REGISTER_SOLVER(blocked_solver)