#include "solvers.h"
#include "LowerTriangularEquation.h"

#include <benchmark/benchmark.h>

static void BM_Solver(benchmark::State &state, const Solver &solve) {
    auto lq = LowerTriangularEquation::CreateRandom(state.range(0));
    for (auto _ : state) {
        solve(lq);
    }
}

int main(int argc, char **argv) {
    for (const auto &p : Solvers::get_solvers()) {
        benchmark::RegisterBenchmark(p.first.c_str(), BM_Solver, p.second)
                ->RangeMultiplier(2)
                ->Range(8, 2048);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}