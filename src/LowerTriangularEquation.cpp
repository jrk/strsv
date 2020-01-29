#include "LowerTriangularEquation.h"

#include <algorithm>
#include <random>
#include <cstdio>

namespace {
    float rand_float() {
        static std::random_device rd;
        static std::default_random_engine gen(rd());
        static std::uniform_real_distribution<float> dist(0, 1);
        return dist(gen);
    }
}

LowerTriangularEquation::LowerTriangularEquation(size_t n)
        : n(n), L(n * n), x(n), b(n) {}

LowerTriangularEquation LowerTriangularEquation::CreateRandom(size_t n) {
    LowerTriangularEquation eq{n};

    // Fill b, but no need to fill x
    std::generate(eq.b.begin(), eq.b.end(), rand_float);

    // Fill L with a lower-triangular, column-major, unit matrix.
    for (int j = 0; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            eq.L[i + j * n] = i == j ? 1.0 : rand_float();
        }
    }

    return eq;
}

void LowerTriangularEquation::dump() const {
    printf("L = \n");
    for (int i = 0; i < n; ++i) {
        printf("\t");
        for (int j = 0; j < n; ++j) {
            printf("%1.02f ", L[i + j * n]);
        }
        printf("\n");
    }

    printf("\nb = \n");
    for (int i = 0; i < n; ++i) {
        printf("\t%1.02f\n", b[i]);
    }

    printf("\nx = \n");
    for (int i = 0; i < n; ++i) {
        printf("\t%1.02f\n", x[i]);
    }
}
