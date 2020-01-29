#ifndef STRSV_SOLVERS_H
#define STRSV_SOLVERS_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <vector>

#include "LowerTriangularEquation.h"

using Solver = std::function<void(LowerTriangularEquation&)>;
void blas_solver(LowerTriangularEquation &eq);

class Solvers {
public:
    Solvers() = delete;

    static void register_solver(const std::string &name, Solver solver) noexcept;

    static const std::unordered_map<std::string, Solver> &get_solvers() { return solvers(); }

private:
    static std::unordered_map<std::string, Solver> &solvers();
};

#define REGISTER_SOLVER(x) \
    struct REGISTER_SOLVER_##x { \
        REGISTER_SOLVER_##x() noexcept { \
            Solvers::register_solver(#x, x); } }; \
    REGISTER_SOLVER_##x registration_##x##_struct{};

#endif //STRSV_SOLVERS_H
