#include "Zombie.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Zombie::Zombie(std::string name) : _name(name)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Zombie::~Zombie()
{
	std::cout << _name << " is being destroyed" << std::endl;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Zombie::announce(void)
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
