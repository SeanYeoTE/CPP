#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
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

	std::cout << YELLOW << "=== Test ShrubberyCreationForm Constructor and Destructor ===" << RESET << std::endl;
	try
	{
		ShrubberyCreationForm form1("Garden");
		std::cout << GREEN << "Form created: " << form1 << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test ShrubberyCreationForm Copy Constructor and Assignment Operator ===" << RESET << std::endl;
	try
	{
		ShrubberyCreationForm form1("Park");
		ShrubberyCreationForm form2 = form1; // Copy constructor
		ShrubberyCreationForm form3("Temp");
		form3 = form1; // Assignment operator
		std::cout << GREEN << "Copied form: " << form2 << RESET << std::endl;
		std::cout << GREEN << "Assigned form: " << form3 << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test ShrubberyCreationForm Execution ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Executor", 1);
		ShrubberyCreationForm form("Backyard");
		b.signForm(form);
		form.execute(b); // Call execute
		std::cout << GREEN << "Form executed successfully." << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	waitForUserInput();
	system("clear");

	return (0);
}