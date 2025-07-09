#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/Intern.hpp"
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
	Intern intern;
	AForm *form = NULL;

	std::cout << YELLOW << "=== Test Intern Creating ShrubberyCreationForm ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("shrubbery", "Garden");
		if (form)
		{
			std::cout << GREEN << "Form created: " << *form << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating ShrubberyCreationForm (Copy and Assignment) ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("shrubbery", "Park");
		if (form)
		{
			AForm *form2 = form; // Pointer copy
			std::cout << GREEN << "Original form: " << *form << RESET << std::endl;
			std::cout << GREEN << "Copied form pointer: " << *form2 << RESET << std::endl;
			delete form; // Only delete once since both pointers point to the same object
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test ShrubberyCreationForm Execution ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Executor", 1);
		form = intern.makeForm("shrubbery", "Backyard");
		if (form)
		{
			b.signForm(*form);
			form->execute(b); // Call execute
			std::cout << GREEN << "Form executed successfully." << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating RobotomyRequestForm ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("robotomy", "RobotLab");
		if (form)
		{
			std::cout << GREEN << "Form created: " << *form << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating RobotomyRequestForm (Copy and Assignment) ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("robotomy", "Factory");
		if (form)
		{
			AForm *form2 = form; // Pointer copy
			std::cout << GREEN << "Original form: " << *form << RESET << std::endl;
			std::cout << GREEN << "Copied form pointer: " << *form2 << RESET << std::endl;
			delete form; // Only delete once since both pointers point to the same object
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test RobotomyRequestForm Execution ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Executor", 1);
		form = intern.makeForm("robotomy", "Workshop");
		if (form)
		{
			b.signForm(*form);
			form->execute(b); // Call execute
			std::cout << GREEN << "Form executed successfully." << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating PresidentialPardonForm ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("presidential", "Citizen");
		if (form)
		{
			std::cout << GREEN << "Form created: " << *form << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating PresidentialPardonForm (Copy and Assignment) ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("presidential", "Individual");
		if (form)
		{
			AForm *form2 = form; // Pointer copy
			std::cout << GREEN << "Original form: " << *form << RESET << std::endl;
			std::cout << GREEN << "Copied form pointer: " << *form2 << RESET << std::endl;
			delete form; // Only delete once since both pointers point to the same object
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test PresidentialPardonForm Execution ===" << RESET << std::endl;
	try
	{
		Bureaucrat b("Executor", 1);
		form = intern.makeForm("presidential", "Target");
		if (form)
		{
			b.signForm(*form);
			form->execute(b); // Call execute
			std::cout << GREEN << "Form executed successfully." << RESET << std::endl;
			delete form;
			form = NULL;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	std::cout << YELLOW << "=== Test Intern Creating Invalid Form ===" << RESET << std::endl;
	try
	{
		form = intern.makeForm("nonexistent", "Invalid");
		if (form)
		{
			std::cout << GREEN << "Form created: " << *form << RESET << std::endl;
			delete form;
			form = NULL;
		}
		else
		{
			std::cout << RED << "Form creation failed as expected." << RESET << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		if (form)
		{
			delete form;
			form = NULL;
		}
	}
	waitForUserInput();
	system("clear");

	return (0);
}
