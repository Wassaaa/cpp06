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

struct ScalarValue {
	bool isValid;
	char charValue;
	int intValue;
	float floatValue;
	double doubleValue;
	bool isPrintableChar;
	bool isWithinIntLimits;
	bool isWithinFloatLimits;
	bool isWithinDoubleLimits;
	bool isSpecial;

	ScalarValue() :
		isValid(false),
		isPrintableChar(false),
		isWithinIntLimits(false),
		isWithinFloatLimits(false),
		isWithinDoubleLimits(false),
		isSpecial(false) {}
};

bool isChar(const std::string& str)
{
	// check for printable char without single quotes
	if (str.length() == 1 && std::isprint(static_cast<unsigned char>(str[0])))
		return true;
	// regex match printable char in single quotes
	std::regex charPattern(R"(^'[[:print:]]'$)");
	return std::regex_match(str, charPattern);
}

bool isInt(const std::string& str)
{
	// regex match int pattern
	std::regex intPattern(R"(^[+-]?\d+$)");
	return std::regex_match(str, intPattern);
}

bool isFloat(const std::string& str)
{
	// check for pseudo literals
	static const std::string special_values[] = {"inff", "+inff", "-inff", "nanf"};
	for (const auto& special : special_values)
		if (str == special) return true;

	// regex match float pattern
	std::regex floatPattern(R"(^[+-]?(\d+\.?\d*|\.\d+)f$)");
	return std::regex_match(str, floatPattern);
}

bool isDouble(const std::string& str)
{
	// check for pseudo literals
	static const std::string special_values[] = {"inf", "+inf", "-inf", "nan"};
	for (const auto& special : special_values)
		if (str == special) return true;

	// regex match double pattern
	std::regex doublePattern(R"(^[+-]?(\d+\.?\d*|\.\d+)$)");
	return std::regex_match(str, doublePattern);
}

static LiteralType detectType(const std::string& str)
{
	// array of my type-function structs.
	static const TypeChecker checkers[] = {
		{CHAR, isChar},
		{INT, isInt},
		{FLOAT, isFloat},
		{DOUBLE, isDouble}
	};

	for (const auto& checker : checkers)
	{
		if (checker.check(str))
			return checker.type;
	}
	return UNKNOWN;
}

static ScalarValue convertChar(const std::string& str)
{
	ScalarValue result;
	result.isValid = true;
	result.charValue = str[1];
	result.intValue = static_cast<int>(result.charValue);
	result.floatValue = static_cast<float>(result.charValue);
	result.doubleValue = static_cast<double>(result.charValue);
	// char is always in limits and printable due to regex pattern
	result.isPrintableChar = true;
	result.isWithinIntLimits = true;
	result.isWithinFloatLimits = true;
	result.isWithinDoubleLimits = true;

	return result;
}

static ScalarValue convertInt(const std::string& str)
{
	ScalarValue result;
	result.isValid = true;
	try
	{
		// make the int
		result.intValue = std::stoi(str);
		result.isWithinIntLimits = true;

		// go for char
		result.charValue = static_cast<char>(result.intValue);
		result.isPrintableChar = std::isprint(result.charValue);

		// cast double, no exception yet, so int always fits in double
		result.doubleValue = static_cast<double>(result.intValue);
		result.isWithinDoubleLimits = true;

		// cast float and check limits
		result.floatValue = static_cast<float>(result.intValue);
		result.isWithinFloatLimits =
			result.intValue >= std::numeric_limits<float>::lowest() &&
			result.intValue <= std::numeric_limits<float>::max();
	}
	catch(const std::exception& e)
	{
		result.isValid = false;
	}
	return result;
}

static ScalarValue convertFloat(const std::string& str)
{
	ScalarValue result;
	result.isValid = true;
	try
	{
		// convert to float, throw if out of range
		result.floatValue = std::stof(str);
		result.isWithinFloatLimits = true;
		result.isSpecial = std::isnan(result.floatValue) || std::isinf(result.floatValue);

		// double can represent all float values
		result.doubleValue = static_cast<double>(result.floatValue);
		result.isWithinDoubleLimits = true;

		// leave everything else false if special value
		if (result.isSpecial)
			return result;

		// cast and handle int
		result.intValue = static_cast<int>(result.floatValue);
		result.isWithinIntLimits =
			result.floatValue >= std::numeric_limits<int>::lowest() &&
			result.floatValue <= std::numeric_limits<int>::max();

		// cast char using the intValue
		result.charValue = static_cast<char>(result.intValue);
		result.isPrintableChar = std::isprint(result.charValue);

	}
	catch (const std::exception& e)
	{
		result.isValid = false;
	}
	return result;
}

static ScalarValue convertDouble(const std::string& str)
{
	ScalarValue result;
	result.isValid = true;
	try
	{
		// convert to double, throw if out of range
		result.doubleValue = std::stod(str);
		result.isWithinDoubleLimits = true;
		result.isSpecial = std::isnan(result.doubleValue) || std::isinf(result.doubleValue);

		// cast to float
		result.floatValue = static_cast<float>(result.doubleValue);
		result.isWithinFloatLimits = result.isSpecial || (
			result.doubleValue >= std::numeric_limits<float>::lowest() &&
			result.doubleValue <= std::numeric_limits<float>::max());

		// leave everything else false if special value
		if (result.isSpecial)
			return result;

		// cast int, valid double fits all ints
		result.intValue = static_cast<int>(result.doubleValue);
		result.isWithinIntLimits = true;

		// cast char using the intValue
		result.charValue = static_cast<char>(result.intValue);
		result.isPrintableChar = std::isprint(result.charValue);

	}
	catch (const std::exception& e)
	{
		result.isValid = false;
	}
	return result;
}

void printScalarValue(ScalarValue& value)
{
		// Print char
		std::cout << "char: ";
		if (!value.isValid || !value.isWithinIntLimits || value.isSpecial)
			std::cout << "impossible";
		else if (!value.isPrintableChar)
			std::cout << "Non displayable";
		else
			std::cout << "'" << value.charValue << "'";
		std::cout << std::endl;

		// Print int
		std::cout << "int: ";
		if (!value.isValid || !value.isWithinIntLimits || value.isSpecial)
			std::cout << "impossible";
		else
			std::cout << value.intValue;
		std::cout << std::endl;

		// Print float
		std::cout << "float: ";
		if (!value.isValid || !value.isWithinFloatLimits)
			std::cout << "impossible";
		else
			std::cout << std::fixed << std::setprecision(1) << value.floatValue << "f";
		std::cout << std::endl;

		// Print double
		std::cout << "double: ";
		if (!value.isValid || !value.isWithinDoubleLimits)
			std::cout << "impossible";
		else
			std::cout << std::fixed << std::setprecision(1) << value.doubleValue;
		std::cout << std::endl;
}

void ScalarConverter::convert(std::string str)
{
	ScalarValue value;

	switch (detectType(str))
	{
	case CHAR:
		value = convertChar(str);
		break;
	case INT:
		value = convertInt(str);
		break;
	case FLOAT:
		value = convertFloat(str);
		break;
	case DOUBLE:
		value = convertDouble(str);
		break;

	default:
		break;
	}

	printScalarValue(value);
}
