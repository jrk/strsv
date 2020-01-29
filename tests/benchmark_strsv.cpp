#include <iostream>
#include <benchmark/benchmark.h>
#include "solvers.h"

static void BM_Solver(benchmark::State &state, const Solver& solve) {
    for (auto _ : state) {
        auto n = state.range(0);
        std::vector<float> b(n), x(n);
        std::vector<float> L(n * n);
        solve(L.data(), x.data(), b.data(), n);
    }
}

int main(int argc, char **argv) {
    for (const auto &p : Solvers::get_solvers()) {
        std::cout << p.first << "\n";
        benchmark::RegisterBenchmark(p.first.c_str(), BM_Solver, p.second)
                ->RangeMultiplier(2)
                ->Range(8, 2048);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}