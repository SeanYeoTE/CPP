#ifndef SCALAR_HPP
# define SCALAR_HPP

# include <cstdlib>
# include <iostream>
# include <limits>
# include <string>
# include <cmath>
# include <map>

class ScalarConverter
{
  private:
	// Data members
	char _char;
	int _int;
	float _float;
	double _double;

	std::string _str;
    int _type;
    
    // Enum for special literal types
    enum SpecialType {
        NOT_SPECIAL,
        NAN_VALUE,
        POS_INF,
        NEG_INF
    };
	
	// Static method to get the singleton instance
	static ScalarConverter& getInstance(void);

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
	

	bool isChar(std::string str) const;
	bool isInt(std::string str) const;
	bool isFloat(std::string str) const;
	bool isDouble(std::string str) const;
	
    // Helper method to check for special literals
    SpecialType checkSpecialLiteral(const std::string &input) const;
    void checktype(const std::string &input);
	void firstconvert(const std::string &input);
	void convertChar(const std::string &input);
	void convertInt(const std::string &input);
	void convertFloat(const std::string &input);
	void convertDouble(const std::string &input);
	
	// Helper functions for displaying scalar types
	void displayChar(double sourceValue, bool isNan, int infSign) const;
	void displayInt(double sourceValue, bool isNan, int infSign) const;
	void displayFloat(double sourceValue, bool isNan, int infSign) const;
	void displayDouble(double sourceValue, bool isNan, int infSign) const;
	
  public:
	static void convert(const std::string &input);
	static void display(void);
};

#endif
