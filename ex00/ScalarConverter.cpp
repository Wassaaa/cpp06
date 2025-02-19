#include "ScalarConverter.hpp"

enum LiteralType {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN
};

struct TypeChecker {
	LiteralType type;
	bool (*check)(const std::string&);
};

bool isChar(const std::string& input)
{
	// check for printable char without single quotes
	if (input.length() == 1 && std::isprint(static_cast<unsigned char>(input[0])))
		return true;
	// regex match printable char in single quotes
	std::regex charPattern(R"(^'[[:print:]]'$)");
	return std::regex_match(input, charPattern);
}

bool isInt(const std::string& input)
{
	// regex match int pattern
	std::regex intPattern(R"(^[+-]?\d+$)");
	return std::regex_match(input, intPattern);
}

bool isFloat(const std::string& input)
{
	// check for pseudo literals
	static const std::string special_values[] = {"inff", "+inff", "-inff", "nanf"};
	for (const auto& special : special_values)
		if (input == special) return true;

	// regex match float pattern
	std::regex floatPattern(R"(^[+-]?(\d+\.?\d*|\.\d+)f$)");
	return std::regex_match(input, floatPattern);
}

bool isDouble(const std::string& input)
{
	// check for pseudo literals
	static const std::string special_values[] = {"inf", "+inf", "-inf", "nan"};
	for (const auto& special : special_values)
		if (input == special) return true;

	// regex match double pattern
	std::regex doublePattern(R"(^[+-]?(\d+\.?\d*|\.\d+)$)");
	return std::regex_match(input, doublePattern);
}

static LiteralType detectType(const std::string& input)
{
	static const TypeChecker checkers[] = {
		{CHAR, isChar},
		{INT, isInt},
		{FLOAT, isFloat},
		{DOUBLE, isDouble}
	};

	for (const auto& checker : checkers)
	{
		if (checker.check(input))
			return checker.type;
	}
	return UNKNOWN;
}

void ScalarConverter::convert(std::string str)
{
	switch (detectType(str))
	{
	case CHAR:
		std::cout << str << " is a CHAR\n";
		break;
	case INT:
		std::cout << str << " is a INT\n";
		break;
	case FLOAT:
		std::cout << str << " is a FLOAT\n";
		break;
	case DOUBLE:
		std::cout << str << " is a DOUBLE\n";
		break;

	default:
		std::cout << str << " is some Unknown stuff\n";
		break;
	}
}
