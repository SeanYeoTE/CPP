#ifndef SCALAR_HPP
# define SCALAR_HPP

# include <cmath>
# include <cstdlib>
# include <iostream>
# include <limits>
# include <string>
# include <iomanip>
# include <sstream>

class ScalarConverter
{
  private:
	// Enum for special literal types
	enum	SpecialType
	{
		NOT_SPECIAL,
		NAN_VALUE,
		POS_INF,
		NEG_INF
	};

	enum	Type
	{
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		UNKNOWN
	};

	Type _type;
	ScalarConverter(void);
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &ans);
	ScalarConverter &operator=(const ScalarConverter &ans);

	static bool isChar(const std::string &str);
	static bool isInt(const std::string &str);
	static bool isFloat(const std::string &str);
	static bool isDouble(const std::string &str);

	// Helper method to check for special literals
	static SpecialType checkSpecialLiteral(const std::string &input);
	static Type checktype(const std::string &input);

	// Helper functions for displaying scalar types
	static void displayChar(double sourceValue, bool isNan, int infSign);
	static void displayInt(double sourceValue, bool isNan, int infSign);
	static void displayFloat(double sourceValue, bool isNan, int infSign);
	static void displayDouble(double sourceValue, bool isNan, int infSign);

  public:
	static void convert(const std::string &input);
};

#endif
