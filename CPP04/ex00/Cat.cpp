#include "Cat.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Cat::Cat()
{
	std::cout << "Cat default constructor called" << std::endl;
	setType("Cat");
}

Cat::Cat(const Cat &src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	setType(src.getType());
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Cat &Cat::operator=(Cat const &rhs)
{
	std::cout << "Cat assignment operator called" << std::endl;
	this->setType(rhs.getType());
	return (*this);
}
/*
** --------------------------------- METHODS ----------------------------------
*/
void Cat::makeSound() const
{
	std::cout << "meow" << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */