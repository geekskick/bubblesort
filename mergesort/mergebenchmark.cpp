#include "benchmark/benchmark.h"
#include "mergesort.hpp"

void mergebenchmark(benchmark::State& state){
    const auto uut = [&state](){
        auto rc = std::vector<int>{{}};
        std::generate_n(std::back_inserter(rc), state.range(0),[](){
            return std::rand();
        });
        return rc;
    }();

    for(auto _ : state){
        mergesort(uut);
    }
}

BENCHMARK(mergebenchmark)->DenseRange(0, 8000, 200);
BENCHMARK_MAIN();
