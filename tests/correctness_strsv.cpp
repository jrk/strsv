#include <cmath>
#include "gtest/gtest.h"
#include "solvers.h"

bool relatively_close(const std::vector<float> &correct, const std::vector<float> &other) {
    float x_y = 0.0f;
    float y = 0.0f;
    int n = correct.size();
    for (int i = 0; i < n; ++i) {
        float diff = (correct[i] - other[i]);
        x_y += diff * diff;
        y += correct[i] * correct[i];
    }
    return sqrtf(x_y / y) < 10 * FLT_EPSILON;
}

TEST(SolverTest, AllValuesClose) {
    auto lte = LowerTriangularEquation::CreateRandom(8);

    blas_solver(lte);
    auto correct_x = lte.x; // copies!

    for (const auto &s : Solvers::get_solvers()) {
        std::fill(lte.x.begin(), lte.x.end(), 0.0f);
        s.second(lte);
        ASSERT_PRED2(relatively_close, correct_x, lte.x);
    }
}
