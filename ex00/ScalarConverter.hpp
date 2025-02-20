#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <cctype>
# include <regex>
# include <limits>
# include <cmath>
# include <iomanip>

template<typename To, typename From>
bool isWithinLimits(From value) {
	return value >= std::numeric_limits<To>::lowest() &&
		value <= std::numeric_limits<To>::max();
}
class ScalarConverter
{
public:

	static void convert(std::string str);

private:
	ScalarConverter() = delete;
	ScalarConverter(const ScalarConverter& other) = delete;
	ScalarConverter& operator=(const ScalarConverter& other) = delete;
	~ScalarConverter() = delete;
};

#endif
