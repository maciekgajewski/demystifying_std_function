#include "function.hh"

#include <iostream>
#include <cassert>

int global_counter()
{
	static int c = 0;
	return c++;
}

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
 	//pr::function<int()> c1 = global_counter;
	
	// construction from lambda
	pr::function<int()> c2 = [c = int{}]() mutable { return c++; };
	
	assert(!!c2);
	assert(c2() == 0);
	assert(c2() == 1);
	
	// copy construction
	auto copy = c2;
	//assert(!!copy);
	//assert(copy() == 2);
	//assert(copy() == 3);
	assert(c2() == 2);
	assert(c2() == 3);
	

}