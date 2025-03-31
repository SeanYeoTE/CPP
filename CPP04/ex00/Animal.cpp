#include "Animal.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Animal::Animal()
{
	std::cout << "Animal default constructor called" << std::endl;
	type = "Animal";
}

Animal::Animal(const Animal &src)
{
	std::cout << "Animal copy constructor called" << std::endl;
	type = src.getType();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Animal &Animal::operator=(Animal const &rhs)
{
	// if ( this != &rhs )
	//{
	// this->_value = rhs.getValue();
	//}
	return (*this);
}

/*
** --------------------------------- METHODS ----------------------------------
*/
void Animal::setType(std::string newType)
{
	type = newType;
}

std::string Animal::getType() const
{
	return (type);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */