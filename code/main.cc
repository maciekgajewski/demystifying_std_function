#include "function.hh"

#include <iostream>

int main()
{
	namespace pr = presentation;
	
	pr::function<int()> counter;
	pr::function<void(int, const std::string&)> print;
	
	
}