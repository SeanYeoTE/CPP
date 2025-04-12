#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <string>

// Add color macros
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

void	waitForUserInput(void)
{
	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int	main(void)
{
	system("clear");
	std::cout << YELLOW << "=== Test Bureaucrat Constructor and Destructor ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("John", 1);
		std::cout << GREEN << b << RESET << std::endl;
	}
	catch (const Bureaucrat::BureaucratException &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Bureaucrat Copy Constructor and Assignment Operator ===" << RESET << std::endl;
	try
	{
		Bureaucrat b1("Alice", 50);
		Bureaucrat b2 = b1; // Copy constructor
		Bureaucrat b3("Temp", 160);
		b3 = b1; // Assignment operator
		std::cout << GREEN << b2 << RESET << std::endl;
		std::cout << GREEN << b3 << RESET << std::endl;
	}
	catch (const Bureaucrat::BureaucratException &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Bureaucrat Increment and Decrement Grade ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Doe", 2);
		b.incrementGrade();
		std::cout << GREEN << b << RESET << std::endl;
		b.decrementGrade();
		std::cout << GREEN << b << RESET << std::endl;
	}
	catch (const Bureaucrat::BureaucratException &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Form Constructor and Destructor ===" << RESET << std::endl;
	try
	{
		Form f("Form1", 1, 150);
		std::cout << GREEN << f << RESET << std::endl;
	}
	catch (const Form::FormException &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Form Copy Constructor and Assignment Operator ===" << RESET << std::endl;
	try
	{
		Form f1("Form2", 50, 100);
		Form f2 = f1; // Copy constructor
		Form f3("TempForm", 75, 125);
		f3 = f1; // Assignment operator
		std::cout << GREEN << f2 << RESET << std::endl;
		std::cout << GREEN << f3 << RESET << std::endl;
	}
	catch (const Form::FormException &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Form beSigned ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Signer", 55);
		Form f("Form3", 50, 100);
		f.beSigned(b.getGrade());
		std::cout << GREEN << f << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	return (0);
}