#include "scalar.hpp"
#include <sstream> // For stringstream

// Constructor
ScalarConverter::ScalarConverter(void)
{
	// Empty constructor
}

// Destructor
ScalarConverter::~ScalarConverter()
{
	// ...existing code...
}

// Copy Constructor
ScalarConverter::ScalarConverter(const ScalarConverter &ans)
{
	this->_char = ans._char;
	this->_int = ans._int;
	this->_float = ans._float;
	this->_double = ans._double;
	this->_str = ans._str;
}

// Assignment Operator
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &ans)
{
	(void)ans;
	return (*this);
}

// Getter and Setter for char
char ScalarConverter::getChar(void) const
{
	return (this->_char);
}

void ScalarConverter::setChar(char c)
{
	this->_char = c;
}

// Getter and Setter for int
int ScalarConverter::getInt(void) const
{
	return (this->_int);
}

void ScalarConverter::setInt(int n)
{
	this->_int = n;
}

// Getter and Setter for float
float ScalarConverter::getFloat(void) const
{
	return (this->_float);
}

void ScalarConverter::setFloat(float f)
{
	this->_float = f;
}

// Getter and Setter for double
double ScalarConverter::getDouble(void) const
{
	return (this->_double);
}

void ScalarConverter::setDouble(double d)
{
	this->_double = d;
}


bool ScalarConverter::isChar(std::string str) const
{
	if (str.length() == 1 && isprint(str[0]))
		return (true);
	return (false);
}

bool ScalarConverter::isInt(std::string str) const
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
			return (false);
	}
	return (true);
}

// Helper method to check for special literals
ScalarConverter::SpecialType ScalarConverter::checkSpecialLiteral(const std::string &input) const
{
    // Remove 'f' suffix if present for uniform checking
    std::string str = input;
    
    if (str.length() > 0 && str[str.length() - 1] == 'f')
    {
        str = str.substr(0, str.length() - 1);
    }
    
    // Check for NaN
    if (str == "nan")
        return NAN_VALUE;
    // Check for positive infinity
    else if (str == "+inf")
        return POS_INF;
    // Check for negative infinity
    else if (str == "-inf")
        return NEG_INF;
    
    return NOT_SPECIAL;
}

bool ScalarConverter::isFloat(std::string str) const
{
    // Check for special float values using the helper method
    SpecialType specialType = checkSpecialLiteral(str);
    if (specialType != NOT_SPECIAL && str.length() > 0 && str[str.length() - 1] == 'f')
        return true;

    size_t dotCount = 0;
    bool hasF = false;

    // Check for 'f' suffix
    if (str.length() > 0 && str[str.length() - 1] == 'f')
    {
        hasF = true;
        str = str.substr(0, str.length() - 1); // Remove 'f' for further checking
    }

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
    return (hasF && dotCount <= 1);
}

bool ScalarConverter::isDouble(std::string str) const
{
    // Check for special double values using the helper method
    SpecialType specialType = checkSpecialLiteral(str);
    if (specialType != NOT_SPECIAL && (str.length() == 0 || str[str.length() - 1] != 'f'))
        return true;

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

void ScalarConverter::checktype(const std::string &input)
{
    // First check if it's a special literal
    SpecialType specialType = checkSpecialLiteral(input);
    
    if (specialType != NOT_SPECIAL)
    {
        // Determine if it's a float or double based on 'f' suffix
        if (input.length() > 0 && input[input.length() - 1] == 'f')
            this->_type = 2; // Float
        else
            this->_type = 3; // Double
    }
    else if (isChar(input))
        this->_type = 0;
    else if (isInt(input))
        this->_type = 1;
    else if (isFloat(input))
        this->_type = 2;
    else if (isDouble(input))
        this->_type = 3;
    else
        this->_type = 3; // Default to double for unrecognized inputs
}

void ScalarConverter::firstconvert(const std::string &input)
{
	int	_type;

	_type = this->_type;
	switch (_type)
	{
	case 0:
		convertChar(input);
		break ;
	case 1:
		convertInt(input);
		break ;
	case 2:
		convertFloat(input);
		break ;
	case 3:
		convertDouble(input);
		break ;
	default:
		throw std::invalid_argument("Invalid type");
		break ;
	}
}

// Static method to get the singleton instance
ScalarConverter& ScalarConverter::getInstance(void)
{
	static ScalarConverter instance;
	return instance;
}

void ScalarConverter::convert(const std::string &input)
{
	// Get the static instance to use the private methods
	ScalarConverter &converter = getInstance();
	
	// Use the instance to check the type and convert
	converter.checktype(input);
	converter.firstconvert(input);
}

void ScalarConverter::convertChar(const std::string &input)
{
	this->_char = input[0];
}

void ScalarConverter::convertInt(const std::string &input)
{
	// Convert to int directly without try-catch
	this->_int = std::atoi(input.c_str());
}

void ScalarConverter::convertFloat(const std::string &input)
{
    // Check if it's a special literal
    SpecialType specialType = checkSpecialLiteral(input);
    
    if (specialType != NOT_SPECIAL)
    {
        // Handle special values
        switch (specialType)
        {
            case NAN_VALUE:
                this->_float = std::numeric_limits<float>::quiet_NaN();
                break;
            case POS_INF:
                this->_float = std::numeric_limits<float>::infinity();
                break;
            case NEG_INF:
                this->_float = -std::numeric_limits<float>::infinity();
                break;
            default:
                break;
        }
        return;
    }

    // Regular float conversion
    // Remove 'f' suffix if present for conversion
    std::string tmp = input;
    if (tmp.length() > 0 && tmp[tmp.length() - 1] == 'f')
        tmp = tmp.substr(0, tmp.length() - 1);
        
    this->_float = std::atof(tmp.c_str());
}

void ScalarConverter::convertDouble(const std::string &input)
{
    // Check if it's a special literal
    SpecialType specialType = checkSpecialLiteral(input);
    
    if (specialType != NOT_SPECIAL)
    {
        // Handle special values
        switch (specialType)
        {
            case NAN_VALUE:
                this->_double = std::numeric_limits<double>::quiet_NaN();
                break;
            case POS_INF:
                this->_double = std::numeric_limits<double>::infinity();
                break;
            case NEG_INF:
                this->_double = -std::numeric_limits<double>::infinity();
                break;
            default:
                break;
        }
        return;
    }

    // Regular double conversion
    this->_double = std::atof(input.c_str());
}

// Helper function to display char value
void ScalarConverter::displayChar(double sourceValue, bool isNan, int infSign) const
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
void ScalarConverter::displayInt(double sourceValue, bool isNan, int infSign) const
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
void ScalarConverter::displayFloat(double sourceValue, bool isNan, int infSign) const
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
		std::cout << floatValue << "f";
	}
	std::cout << std::endl;
}

// Helper function to display double value
void ScalarConverter::displayDouble(double sourceValue, bool isNan, int infSign) const
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

void ScalarConverter::display(void)
{
	// Get the values from the static instance used in convert
	ScalarConverter &converter = getInstance();
	
	// Get the source value based on the identified type
	double sourceValue;
	bool isNan = false;
	int infSign = 0; // 0 for not inf, 1 for +inf, -1 for -inf
	
	// Extract source value and check for special types
	switch (converter._type)
	{
	case 0: // char
		sourceValue = static_cast<double>(converter._char);
		break;
	case 1: // int
		sourceValue = static_cast<double>(converter._int);
		break;
	case 2: // float
		sourceValue = static_cast<double>(converter._float);
		if (std::isnan(converter._float))
			isNan = true;
		else if (std::isinf(converter._float))
			infSign = (converter._float > 0) ? 1 : -1;
		break;
	case 3: // double
		sourceValue = converter._double;
		if (std::isnan(converter._double))
			isNan = true;
		else if (std::isinf(converter._double))
			infSign = (converter._double > 0) ? 1 : -1;
		break;
	default:
		sourceValue = 0.0;
		break;
	}
	
	// Display all types using helper functions
	converter.displayChar(sourceValue, isNan, infSign);
	converter.displayInt(sourceValue, isNan, infSign);
	converter.displayFloat(sourceValue, isNan, infSign);
	converter.displayDouble(sourceValue, isNan, infSign);
}
