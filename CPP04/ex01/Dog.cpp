#include "Dog.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Dog::Dog()
{
	std::cout << "Dog default constructor called" << std::endl;
	setType("Dog");
	brain = new Brain();
}

Dog::Dog(const Dog &src) : Animal(src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	setType(src.getType());
	brain = new Brain(*src.brain); // Deep copy of brain
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete brain;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Dog &Dog::operator=(Dog const &rhs)
{
	std::cout << "Dog assignment operator called" << std::endl;
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

void Dog::makeSound() const
{
	std::cout << "woof" << std::endl;
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Brain* Dog::getBrain() const
{
	return (this->brain);
}

bool Dog::addIdea(std::string idea)
{
	return this->brain->addIdea(idea);
}

std::string Dog::getIdea(int index) const
{
	return this->brain->getIdea(index);
}

/* ************************************************************************** */
