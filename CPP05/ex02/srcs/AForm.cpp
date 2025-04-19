#include "../includes/AForm.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

AForm::AForm() : _name("default"), _isSigned(false), _gradeToSign(150),
	_gradeToExecute(150)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : _name(name),
	_isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
	std::cout << "AForm constructor called" << std::endl;
}

AForm::AForm(AForm const &src) : _name(src.getName()),
	_isSigned(src.getIsSigned()), _gradeToSign(src.getGradeToSign()),
	_gradeToExecute(src.getGradeToExecute())
{
	std::cout << "AForm copy constructor called" << std::endl;
	// *this = src;
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

AForm::~AForm()
{
	std::cout << "AForm destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

AForm &AForm::operator=(AForm const &rhs)
{
	std::cout << "AForm assignment operator called" << std::endl;
	this->_isSigned = rhs.getIsSigned();
	return (*this);
}

std::ostream &operator<<(std::ostream &o, AForm const &i)
{
	std::cout << i.getName() << " , grade to sign " << i.getGradeToSign() << " , grade to execute " << i.getGradeToExecute();
	return (o);
}

/*
** --------------------------------- METHODS ----------------------------------
*/
const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string &AForm::getName() const
{
	return (_name);
}

const bool &AForm::getIsSigned() const
{
	return (_isSigned);
}

const int &AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

const int &AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void AForm::setIsSigned(bool ran)
{
	_isSigned = ran;
}

void AForm::beSigned(int grade)
{
	if (grade > _gradeToSign)
		throw AForm::GradeTooLowException();
	else
	{
		_isSigned = true;
		std::cout << "AForm " << _name << " signed by grade " << grade << std::endl;
	}
}
/* ************************************************************************** */