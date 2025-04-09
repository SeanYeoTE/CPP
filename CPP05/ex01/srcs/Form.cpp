#include "../includes/Form.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Form::Form() : _name("default"), _isSigned(false), _gradeToSign(150),
	_gradeToExecute(150)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : _name(name),
	_isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	std::cout << "Form constructor called" << std::endl;
}

Form::Form(Form const &src) : _name(src.getName()),
	_isSigned(src.getIsSigned()), _gradeToSign(src.getGradeToSign()),
	_gradeToExecute(src.getGradeToExecute())
{
	std::cout << "Form copy constructor called" << std::endl;
	// *this = src;
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Form &Form::operator=(Form const &rhs)
{
	this->_isSigned = rhs.getIsSigned();
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Form const &i)
{
	std::cout << i.getName() << " , form grade to sign " << i.getGradeToSign() << " , form grade to execute " << i.getGradeToExecute() << std::endl;
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/
const char *Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string &Form::getName() const
{
	return (_name);
}

const bool &Form::getIsSigned() const
{
	return (_isSigned);
}

const int &Form::getGradeToSign() const
{
	return (_gradeToSign);
}

const int &Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void Form::beSigned(int grade)
{
	if (grade > _gradeToSign)
		throw Form::GradeTooLowException();
	else
	{
		_isSigned = true;
		std::cout << "Form " << _name << " signed by grade " << grade << std::endl;
	}
}
/* ************************************************************************** */