#include <benchmark/benchmark.h>

static void BM_StringCreation(benchmark::State &state) {
    for (auto _ : state) {
        std::string empty_string;
    }
}

int main(int argc, char **argv) {
    benchmark::RegisterBenchmark("BM_StringCreation", BM_StringCreation);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}