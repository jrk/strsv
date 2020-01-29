#include <utility>

#include "solvers.h"

void Solvers::register_solver(const std::string &name, Solver solver) noexcept {
    try {
        solvers[name] = std::move(solver);
    } catch (...) { /* just ignore the solver */ }
}

std::unordered_map<std::string, Solver> Solvers::solvers{};