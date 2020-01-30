#include <cmath>
#include "gtest/gtest.h"
#include "solvers.h"

#include <cstdio>

bool relatively_close(const std::vector<float> &correct, const std::vector<float> &other) {
    float x_y = 0.0f;
    float y = 0.0f;
    int n = correct.size();
    for (int i = 0; i < n; ++i) {
        float diff = (other[i] - correct[i]);
        x_y += diff * diff;
        y += correct[i] * correct[i];
    }
    return sqrtf(x_y / y) < (3.0f * n * n) * FLT_EPSILON;
}

TEST(SolverTest, AllValuesClose) {
    auto lte = LowerTriangularEquation::CreateRandom(468);

    blas_solver(lte);
    auto correct_x = lte.x; // copies!

    for (const auto &s : Solvers::get_solvers()) {
        printf("%s\n", s.first.c_str());
        for (int i = 0; i < 100; ++i) {
            // reset x
            std::fill(lte.x.begin(), lte.x.end(), 0.0f);

            // call the solver
            s.second(lte);

            // check correctness
            ASSERT_PRED2(relatively_close, correct_x, lte.x);
        }
    }
}
