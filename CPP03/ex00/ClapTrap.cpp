#include "ClapTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ClapTrap::ClapTrap(std::string name)
{
	this->name = name;
	hitPoints = 10;
	energyPoints = 10;
	attackDamage = 0;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
	name = src.name;
	hitPoints = src.hitPoints;
	energyPoints = src.energyPoints;
	attackDamage = src.attackDamage;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ClapTrap::~ClapTrap()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

// std::ostream &operator<<(std::ostream &o, ClapTrap const &i)
// {
// 	// o << "Value = " << i.getValue();
// 	return o;
// }

/*
** --------------------------------- METHODS ----------------------------------
*/

void ClapTrap::printEnergyPoints()
{
	std::cout << "ClapTrap " << name << " has " << energyPoints << " energy points remaining." << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
	if (energyPoints <= 0 || hitPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " has no hit points or energy points to attack!" << std::endl;
		return;
	}
	else
	{
		std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
		energyPoints--;
		printEnergyPoints();
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	hitPoints -= amount;
	std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energyPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " has no hit points or energy points to repair!" << std::endl;
		return;
	}
	else
	{
		hitPoints += amount;
		energyPoints--;
		std::cout << "ClapTrap " << name << " is repaired " << amount << " points!" << std::endl;
		printEnergyPoints();
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */