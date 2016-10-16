#include "function.hh"

#include <iostream>
#include <cassert>

int global_counter()
{
	static int c = 0;
	return c++;
}

int increment(int& v)
{
	return v++;
}

struct counter_functor
{
	int c = 0;
	int operator()() { return c++; }
};

int main()
{
	namespace pr = presentation;
	
	// tests

	// defaul construction
	pr::function<int()> c0;
	assert(!c0);
	
	// caling empty throws
	try {
		c0();
		assert(false && "Should call");
	} catch(const std::bad_function_call&) {
		// OK=
	} catch(...) {
		assert(false && "Should throw std::bad_function_call");
	}
	
	// construction from function pointer
	pr::function<int()> c1 = global_counter;
	assert(!!c1);
	assert(c1() == 0);
	assert(c1() == 1);
	assert(c1() == 2);
	
	// construction from lambda
	pr::function<int()> c2 = [c = int{}]() mutable { return c++; };
	
	assert(!!c2);
	assert(c2() == 0);
	assert(c2() == 1);
	
	// copy construction
	auto copy = c2;
	assert(!!copy);
	assert(copy() == 2);
	assert(copy() == 3);
	// the original's state remains unchanged
	assert(c2() == 2);
	assert(c2() == 3);
	
	// bind
	int ctr = 0;
	pr::function<int()> b = std::bind(increment, std::ref(ctr));
	assert(!!b);
	assert(b() == 0);
	assert(b() == 1);
	assert(b() == 2);
	assert(ctr == 3);
	
	// type
	const pr::function<int()> ff = counter_functor{};
	assert(ff.target_type() == typeid(counter_functor));
	assert(ff() == 0);
	assert(ff() == 1);
	assert(ff() == 2);
}