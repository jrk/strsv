#ifndef STRSV_SOLVERS_H
#define STRSV_SOLVERS_H

#include <string>
#include <unordered_map>
#include <memory>
#include "solver.h"

class Solvers {
public:
    using TSolver = std::unique_ptr<Solver>(*)();

    Solvers() = delete;

    static bool register_solver(const std::string &name);

private:
    static std::unordered_map<std::string, TSolver> solvers;
};

#endif //STRSV_SOLVERS_H
