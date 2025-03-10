#include "ScavTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

// ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
// {
// 	std::cout << "ScavTrap " << name << " created." << std::endl;
// }

// ScavTrap::ScavTrap(const ScavTrap &src)
// {
// }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

// ScavTrap::~ScavTrap()
// {
// 	std::cout << "ScavTrap " << name << " destroyed." << std::endl;
// }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << getName() << " is now in Gatekeeper mode." << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */