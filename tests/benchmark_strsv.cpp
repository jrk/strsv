#include <iostream>
#include <benchmark/benchmark.h>
#include "solvers.h"

static void BM_Solver(benchmark::State &state, Solver s) {
    for (auto _ : state) {
        std::string empty_string;
    }
}

int main(int argc, char **argv) {
    for (const auto &p : Solvers::get_solvers()) {
        std::cout << p.first << "\n";
        benchmark::RegisterBenchmark(p.first.c_str(), BM_Solver, p.second);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}