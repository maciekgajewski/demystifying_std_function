#include <benchmark/benchmark.h>

#include <functional>


struct counter_ftor
{
	int c = 0;
	int operator() () 
	{
		return c++;
	}
};

int global_counter();

struct icounter
{
	virtual int count() = 0;
};

icounter& get_counter();

volatile int out;
using StdFun = std::function<int()>;

static const int ITER = 100;

void function(benchmark::State& state, const StdFun& f)
{
	while(state.KeepRunning())
		for(int i =0 ;i < ITER; i++)
			benchmark::DoNotOptimize(out = f());
}

void raw_functor(benchmark::State& state)
{
	counter_ftor f{};
	while(state.KeepRunning())
		for(int i =0 ;i < ITER; i++)
			benchmark::DoNotOptimize(out = f());
}

void raw_function(benchmark::State& state)
{
	while(state.KeepRunning())
		for(int i =0 ;i < ITER; i++)
			benchmark::DoNotOptimize(out = global_counter());
}

void virtual_fun(benchmark::State& state)
{
	icounter& c = get_counter();
	while(state.KeepRunning())
		for(int i =0 ;i < ITER; i++)
			benchmark::DoNotOptimize(out = c.count());
}



StdFun fun_holding_functor = counter_ftor{};
BENCHMARK_CAPTURE(function, function_holding_functor, fun_holding_functor);

StdFun fun_holding_function = &global_counter;
BENCHMARK_CAPTURE(function, function_holding_function, fun_holding_function);

BENCHMARK(raw_functor);
BENCHMARK(raw_function);
BENCHMARK(virtual_fun);

BENCHMARK_MAIN();