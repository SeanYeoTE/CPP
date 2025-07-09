#include "Ice.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Ice::Ice()  : AMateria("ice")
{
	// std::cout << "Ice default constructor called" << std::endl;
	// this->_type = "ice";
}

Ice::Ice(const Ice &src) : AMateria("ice")
{
	// std::cout << "Ice constructor called" << std::endl;
	(void)src;
	// this->_type = src.getType();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Ice::~Ice()
{
	// std::cout << "Ice destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Ice &Ice::operator=(Ice const &rhs)
{
	// std::cout << "Ice assignation operator called" << std::endl;
	if (this != &rhs)
	{
		this->_type = rhs.getType();
	}
	return (*this);
}

/*
** --------------------------------- METHODS ----------------------------------
*/
AMateria *Ice::clone() const
{
	// std::cout << "Ice clone called" << std::endl;
	return (new Ice(*this));
}

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
