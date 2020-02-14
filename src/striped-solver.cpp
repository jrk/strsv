#include "solvers.h"
#include <immintrin.h>

typedef float v4sf __attribute__((vector_size(16), aligned(1)));

// TODO: for simplicity, assumes n%4=0
void striped_solver(LowerTriangularEquation &eq) {
  int n = eq.n;

  float *L = eq.L.data();
  float *x = eq.x.data();

  std::copy(eq.b.begin(), eq.b.end(), eq.x.begin());

  for (int di = 0; di < n; di += 4) {
    __m128 x_acc = _mm_loadu_ps(&x[di]);

    // leading squares
    for (int dj = 0; dj < di; dj += 4) {
      for (int k = 0; k < 4; ++k) {
        __m128 bx = _mm_broadcast_ss(&x[dj + k]);
        __m128 Lc = _mm_loadu_ps(&L[di + n * (dj + k)]);
        x_acc -= Lc * bx;
      }
    }

    // ending triangle -- slow.
    x_acc[1] -= x_acc[0] * L[di + 1 + n * (di + 0)];
    x_acc[2] -= x_acc[0] * L[di + 2 + n * (di + 0)];
    x_acc[3] -= x_acc[0] * L[di + 3 + n * (di + 0)];
    x_acc[2] -= x_acc[1] * L[di + 2 + n * (di + 1)];
    x_acc[3] -= x_acc[1] * L[di + 3 + n * (di + 1)];
    x_acc[3] -= x_acc[2] * L[di + 3 + n * (di + 2)];

    _mm_store_ps(&x[di], x_acc);
  }
}

REGISTER_SOLVER(striped_solver)