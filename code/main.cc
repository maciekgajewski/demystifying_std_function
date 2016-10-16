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
	
	pr::function<int()> c0;
 	//pr::function<int()> c1 = global_counter;
 	pr::function<int()> c2 = [c = int{}]() mutable { return c++; };
	
	assert(c2() == 0);
	assert(c2() == 1);
	std::cout << c2() << std::endl;
	std::cout << c2() << std::endl;
	
	
}