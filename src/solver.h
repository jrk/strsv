#ifndef STRSV_SOLVER_H
#define STRSV_SOLVER_H

class Solver {
public:
    virtual ~Solver() = default;

    virtual void solve_lower(float *L, float *x, float *b, int n) = 0;
};

#endif //STRSV_SOLVER_H
