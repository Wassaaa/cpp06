#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <cctype>
# include <regex>
# include <limits>
# include <cmath>
# include <iomanip>

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
