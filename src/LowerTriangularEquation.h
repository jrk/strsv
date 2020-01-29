#ifndef STRSV_LOWERTRIANGULAREQUATION_H
#define STRSV_LOWERTRIANGULAREQUATION_H

#include <vector>

struct LowerTriangularEquation {
    explicit LowerTriangularEquation(size_t n);

    LowerTriangularEquation(const LowerTriangularEquation &) = default;

    static LowerTriangularEquation CreateRandom(size_t n);
    void dump() const;

    int n;
    std::vector<float> L;
    std::vector<float> x;
    std::vector<float> b;
};


#endif //STRSV_LOWERTRIANGULAREQUATION_H
