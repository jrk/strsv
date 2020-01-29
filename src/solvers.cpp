#include <utility>

#include "solvers.h"

void Solvers::register_solver(const std::string &name, Solver solver) noexcept {
    try {
        solvers().emplace(name, std::move(solver));
    } catch (...) { /* just ignore the exception */ }
}

std::unordered_map<std::string, Solver> &Solvers::solvers() {
    static std::unordered_map<std::string, Solver> s;
    return s;
}