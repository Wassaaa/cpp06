#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <random>

Base *generate(void)
{
	switch (rand() % 3)
	{
	case 0:
		std::cout << "Generated        A" << std::endl;
		return new A();
	case 1:
		std::cout << "Generated        B" << std::endl;
		return new B();
	case 2:
		std::cout << "Generated        C" << std::endl;
		return new C();
	default:
		return nullptr;
	};
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e){}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
	}
	catch(const std::exception& e){}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
	}
	catch(const std::exception& e){}
}

int main()
{
	srand(time(0));

	int i = 10;
	while (i--)
	{
		Base* ptr = generate();
		std::cout << "Identify by ptr: ";
		identify(ptr);
		std::cout << "identify by ref: ";
		identify(*ptr);

		if (ptr != nullptr)
			delete ptr;
	}
}
