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

    __m128 x_cur = _mm_loadu_ps(&x[di]);

    // leading squares
    for (int bj = 0; bj < bi; ++bj) {
      int dj = 4 * bj;
      __m128 bx[4];
      for (int k = 0; k < 4; ++k) {
        bx[k] = _mm_broadcast_ss(&x[dj + k]);
      }
      __m128 Lc[4];
      for (int k = 0; k < 4; ++k) {
        Lc[k] = _mm_loadu_ps(&L[di + n * (dj + k)]);
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

    _mm_store_ps(&x[di], x_cur);
  }
}

REGISTER_SOLVER(striped_solver)