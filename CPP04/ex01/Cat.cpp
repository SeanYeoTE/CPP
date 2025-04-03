#include "Cat.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Cat::Cat()
{
	std::cout << "Cat default constructor called" << std::endl;
	setType("Cat");
	brain = new Brain();
}

Cat::Cat(const Cat &src) : Animal(src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	setType(src.getType());
	brain = new Brain(*src.brain); // Deep copy of brain
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete brain;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Cat &Cat::operator=(Cat const &rhs)
{
	std::cout << "Cat assignment operator called" << std::endl;
	if (this != &rhs)
	{
		this->setType(rhs.getType());
		
		// Deep copy of brain
		delete this->brain;
		this->brain = new Brain(*rhs.brain);
	}
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

Brain* Cat::getBrain() const
{
	return (this->brain);
}

bool Cat::addIdea(std::string idea)
{
	return this->brain->addIdea(idea);
}

std::string Cat::getIdea(int index) const
{
	return this->brain->getIdea(index);
}

/* ************************************************************************** */
