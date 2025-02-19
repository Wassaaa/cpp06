#include "ScalarConverter.hpp"

int main()
{
	// Test integer conversions
	ScalarConverter::convert("42");
	ScalarConverter::convert("-42");

	// Test float conversions
	ScalarConverter::convert("42.0f");
	ScalarConverter::convert("-42.42f");

	// Test double conversions
	ScalarConverter::convert("42.0");
	ScalarConverter::convert("-42.42");

	// Test char conversions
	ScalarConverter::convert("'a'");
	ScalarConverter::convert("'Z'");

	// Test special values
	ScalarConverter::convert("inf");
	ScalarConverter::convert("+inf");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("nan");

	// Test edge cases
	ScalarConverter::convert("0");
	ScalarConverter::convert("");
	ScalarConverter::convert("hello");

	return 0;
}
