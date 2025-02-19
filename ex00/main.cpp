#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat b1("Alice", 1);
		std::cout << b1 << std::endl;
		b1.incrementGrade(); // This should throw an exception
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat b2("Bob", 150);
		std::cout << b2 << std::endl;
		b2.decrementGrade(); // This should throw an exception
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat b3("Charlie", 75);
		std::cout << b3 << std::endl;
		b3.incrementGrade();
		std::cout << b3 << " after increment" << std::endl;
		b3.decrementGrade();
		std::cout << b3 << " after decrement" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
