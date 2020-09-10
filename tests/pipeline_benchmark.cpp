#include <array>
#include <cstdint>
#include <tuple>

#include "benchmark/benchmark.h"
#include "dynamic_tasks.hpp"
#include "static_pipeline.hpp"
#include "static_tasks.hpp"

/**
    Results on release build with CPU scaling disabled

    2020-09-10 20:43:36
    Running pipeline_benchmark
    Run on (8 X 4000 MHz CPU s)
    CPU Caches:
      L1 Data 32K (x4)
      L1 Instruction 32K (x4)
      L2 Unified 256K (x4)
      L3 Unified 8192K (x1)
    Load Average: 0.64, 0.69, 0.72
 */

constexpr int kThreads = 1;
constexpr benchmark::IterationCount kIterations = 2000000;
constexpr int kRepetitions = 10;
constexpr bool kReportAggregatesOnly = true;
constexpr std::int64_t kBytesProcessed = 1;

static void BM_StaticPipeline(benchmark::State &state)
{
    using namespace static_tasks;

    Data data{};

    using Tasks = std::tuple<A, A, B, A, C>;
    Tasks tasks{
        A{data}, A{data}, B{data}, A{data}, C{data},
    };

    static_pipeline::Pipeline<Tasks> pipeline{tasks};

    for (auto _ : state) {
        pipeline.Run();
    }
    state.SetBytesProcessed(kBytesProcessed);

    assert(data.x > 0);
}

BENCHMARK(BM_StaticPipeline)
    ->UseRealTime()
    ->MeasureProcessCPUTime()
    ->Threads(kThreads)
    ->Iterations(kIterations)
    ->Repetitions(kRepetitions)
    ->ReportAggregatesOnly(kReportAggregatesOnly);

static void BM_DynamicPipeline(benchmark::State &state)
{
    using namespace dynamic_tasks;

    Data data{};

    using Tasks = std::array<dynamic_pipeline::Task *, 5>;
    A a{data};
    B b{data};
    C c{data};
    Tasks tasks{
        &a, &a, &b, &a, &c,
    };

    dynamic_pipeline::Pipeline<Tasks> pipeline{tasks};

    for (auto _ : state) {
        pipeline.Run();
    }
    state.SetBytesProcessed(kBytesProcessed);

    assert(data.x > 0);
}

BENCHMARK(BM_DynamicPipeline)
    ->UseRealTime()
    ->MeasureProcessCPUTime()
    ->Threads(kThreads)
    ->Iterations(kIterations)
    ->Repetitions(kRepetitions)
    ->ReportAggregatesOnly(kReportAggregatesOnly);

BENCHMARK_MAIN();
