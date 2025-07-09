#include "../includes/RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(void) : AForm("RobotomyRequestForm",
	72, 45)
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string name) : AForm("RobotomyRequestForm",
	72, 45), _target(name)
{
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other),
	_target(other._target)
{
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	std::cout << "RobotomyRequestForm assignment operator called" << std::endl;
	_target = other._target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!this->getIsSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();

	std::srand(std::time(0));
	std::cout << "* Drilling Noises *" << std::endl;
	if (std::rand() % 2)
	{
		std::cout << _target << " has been robotomized successfully" << std::endl;
	}
	else
	{
		std::cout << "Robotomy has failed" << std::endl;
	}
}