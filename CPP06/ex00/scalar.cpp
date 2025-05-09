#include "scalar.hpp"

// Constructor
ScalarConverter::ScalarConverter(void)
{
	// Empty constructor
}

// Destructor
ScalarConverter::~ScalarConverter()
{
}

// Copy Constructor
ScalarConverter::ScalarConverter(const ScalarConverter &ans)
{
    (void)ans;
}

// Assignment Operator
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &ans)
{
	(void)ans;
	return (*this);
}


bool ScalarConverter::isChar(const std::string &str)
{
	if (str.length() == 1 && isprint(str[0]))
		return (true);
	return (false);
}

bool ScalarConverter::isInt(const std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
			return (false);
	}
	return (true);
}

// Helper method to check for special literals
ScalarConverter::SpecialType ScalarConverter::checkSpecialLiteral(const std::string &input)
{
    // Remove 'f' suffix if present for uniform checking
    std::string str = input;
    if (str.length() > 0 && str[str.length() - 1] == 'f' && str[str.length() - 2] == 'f')
    {
        str = str.substr(0, str.length() - 1);
    }
    // Check for NaN
    if (str == "nan" || str == "nanf")
        return NAN_VALUE;
    // Check for positive infinity
    else if (str == "+inf" || str == "inf")
        return POS_INF;
    // Check for negative infinity
    else if (str == "-inf")
        return NEG_INF;
    
    return NOT_SPECIAL;
}

bool ScalarConverter::isFloat(const std::string &str)
{
    size_t dotCount = 0;
    bool hasF = false;

    // Check for 'f' suffix
    if (str.length() > 0 && str[str.length() - 1] == 'f')
    {
        hasF = true;
    }
    for (size_t i = 0; i < str.length() - 1; i++)
    {
        if (str[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
                return (false);
        }
        else if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
            return (false);
    }
    return (hasF && dotCount <= 1);
}

bool ScalarConverter::isDouble(const std::string &str)
{
    size_t dotCount = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
                return (false);
        }
        else if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
            return (false);
    }
    return (dotCount == 1);
}

ScalarConverter::Type ScalarConverter::checktype(const std::string &input)
{
    // First check if it's a special literal
    SpecialType specialType = checkSpecialLiteral(input);
    
    if (specialType != NOT_SPECIAL)
    {
        // Determine if it's a float or double based on 'f' suffix
        if (input.length() > 0 && input[input.length() - 1] == 'f')
            return FLOAT; // Float
        else
            return DOUBLE; // Double
    }
    else if (isInt(input))
        return INT;
    else if (isFloat(input))
        return FLOAT;
    else if (isDouble(input))
        return DOUBLE;
    else if (isChar(input))
        return CHAR;
    else
        return UNKNOWN;
}

// Helper function to display char value
void ScalarConverter::displayChar(double sourceValue, bool isNan, int infSign)
{
	std::cout << "char: ";
	if (isNan || infSign != 0 || sourceValue < 0 || sourceValue > 127)
		std::cout << "impossible";
	else if (!isprint(static_cast<int>(sourceValue)))
		std::cout << "Non displayable";
	else
	{
		char charValue = static_cast<char>(sourceValue);
		std::cout << "'" << charValue << "'";
	}
	std::cout << std::endl;
}

// Helper function to display int value
void ScalarConverter::displayInt(double sourceValue, bool isNan, int infSign)
{
	std::cout << "int: ";
	if (isNan || infSign != 0 || 
		sourceValue < std::numeric_limits<int>::min() || 
		sourceValue > std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
	{
		int intValue = static_cast<int>(sourceValue);
		std::cout << intValue;
	}
	std::cout << std::endl;
}

// Helper function to display float value
void ScalarConverter::displayFloat(double sourceValue, bool isNan, int infSign)
{
	std::cout << "float: ";
	if (isNan)
		std::cout << "nanf";
	else if (infSign != 0)
	{
		if (infSign > 0)
			std::cout << "+inff";
		else
			std::cout << "-inff";
	}
	else if (sourceValue < -std::numeric_limits<float>::max() || 
			 sourceValue > std::numeric_limits<float>::max())
		std::cout << "impossible";
	else
	{
		float floatValue = static_cast<float>(sourceValue);
		std::cout << std::fixed << std::setprecision(1) << floatValue << "f";
	}
	std::cout << std::endl;
}

// Helper function to display double value
void ScalarConverter::displayDouble(double sourceValue, bool isNan, int infSign)
{
	std::cout << "double: ";
	if (isNan)
		std::cout << "nan";
	else if (infSign != 0)
	{
		if (infSign > 0)
			std::cout << "+inf";
		else
			std::cout << "-inf";
	}
	else
		std::cout << sourceValue;
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& input)
{
    // Identify the type
    Type type = checktype(input);
    
    // Values to be used for display
    double value = 0.0;
    bool isNan = false;
    int infSign = 0;  // 0: not inf, 1: +inf, -1: -inf
    
    // Process based on type
    switch (type) {
        case CHAR:
            value = static_cast<double>(input[0]);
            break;
        case INT:
            value = static_cast<double>(std::atoi(input.c_str()));
            break;
        case FLOAT:
        case DOUBLE: {
            SpecialType specialType = checkSpecialLiteral(input);
            if (specialType != NOT_SPECIAL) {
                isNan = (specialType == NAN_VALUE);
                infSign = (specialType == POS_INF) ? 1 : 
                          (specialType == NEG_INF) ? -1 : 0;
            } else {
                // Remove 'f' suffix if present
                std::string tmp = input;
                if (type == FLOAT && tmp.length() > 0 && tmp[tmp.length() - 1] == 'f')
                    tmp = tmp.substr(0, tmp.length() - 1);
                
                std::stringstream ss(tmp);
                ss >> value;
                // Check for special values from the conversion result
                if (std::isnan(value))
                    isNan = true;
                else if (std::isinf(value))
                    infSign = (value > 0) ? 1 : -1;
            }
            break;
        }
        default:
            // Handle unknown type
            std::cout << "Error: Unknown type" << std::endl;
            return;
    }
    // Display all conversions
    displayChar(value, isNan, infSign);
    displayInt(value, isNan, infSign);
    displayFloat(value, isNan, infSign);
    displayDouble(value, isNan, infSign);
}
