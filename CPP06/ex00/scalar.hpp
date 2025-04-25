#ifndef SCALAR_HPP
# define SCALAR_HPP

# include <cmath>
# include <cstdlib>
# include <iostream>
# include <limits>
# include <map>
# include <string>

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

	char getChar(void) const;
	void setChar(char c);
	int getInt(void) const;
	void setInt(int n);
	float getFloat(void) const;
	void setFloat(float f);
	double getDouble(void) const;
	void setDouble(double d);

	static bool isChar(const std::string &str);
	static bool isInt(const std::string &str);
	static bool isFloat(const std::string &str);
	static bool isDouble(const std::string &str);

	// Helper method to check for special literals
	static SpecialType checkSpecialLiteral(const std::string &input);
	static Type checktype(const std::string &input);
	// void firstconvert(const std::string &input);
	// void convertChar(const std::string &input);
	// void convertInt(const std::string &input);
	// void convertFloat(const std::string &input);
	// void convertDouble(const std::string &input);

	// Helper functions for displaying scalar types
	static void displayChar(double sourceValue, bool isNan, int infSign);
	static void displayInt(double sourceValue, bool isNan, int infSign);
	static void displayFloat(double sourceValue, bool isNan, int infSign);
	static void displayDouble(double sourceValue, bool isNan, int infSign);

  public:
	static void convert(const std::string &input);
	static void display(void);
};

#endif
