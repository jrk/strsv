#include "solvers.h"
#include <immintrin.h>

typedef float v4sf __attribute__((vector_size(16), aligned(1)));

// TODO: for simplicity, assumes n%4=0
void striped_solver(LowerTriangularEquation &eq) {
  int n = eq.n;
  int nb = n / 4;

  float *L = eq.L.data();
  float *x = eq.x.data();

  std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());

  for (int bi = 0; bi < nb; ++bi) {
    int di = 4 * bi;

    v4sf x_cur = *(v4sf *)(&x[di]);

    // leading squares
    for (int bj = 0; bj < bi; ++bj) {
      int dj = 4 * bj;
      v4sf bx[4];
      for (int k = 0; k < 4; ++k) {
        bx[k] = (v4sf){eq.x[dj + k], eq.x[dj + k], eq.x[dj + k], eq.x[dj + k]};
      }
      v4sf Lc[4];
      for (int k = 0; k < 4; ++k) {
        Lc[k] = *(v4sf *)(&eq.L[di + n * (dj + k)]);
      }
      for (int k = 0; k < 4; ++k) {
        x_cur -= Lc[k] * bx[k];
      }
    }

    // ending triangle
    int bj = bi;
    int dj = 4 * bj;
    for (int j = 0; j < 4; ++j) {
      int L_j = dj + j;
      for (int i = j + 1; i < 4; ++i) {
        int L_i = di + i;
        x_cur[i] -= x_cur[j] * L[L_i + n * L_j];
      }
    }

    *(v4sf *)(&x[di]) = x_cur;
  }
}

REGISTER_SOLVER(striped_solver)