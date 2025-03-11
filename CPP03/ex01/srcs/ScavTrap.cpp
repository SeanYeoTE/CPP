#include "ScavTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	setHitPoints(100);	 // Use setter method
	setEnergyPoints(50); // Use setter method
	setAttackDamage(20); // Use setter method
}

// ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
// {
// 	// Copy the specific attributes if any
// 	setHitPoints(src.getHitPoints());
// 	setEnergyPoints(src.getEnergyPoints());
// 	setAttackDamage(src.getAttackDamage());
// }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ScavTrap::~ScavTrap()
{
	// std::cout << "ScavTrap " << getName() << " destroyed." << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
std::ostream &operator<<(std::ostream &o, ScavTrap const &i)
{
	o << "ScavTrap " << i.getName() << ":" << std::endl;
	o << "Hit Points: " << i.getHitPoints() << std::endl;
	o << "Energy Points: " << i.getEnergyPoints() << std::endl;
	o << "Attack Damage: " << i.getAttackDamage();
	return o;
}
/*
** --------------------------------- METHODS ----------------------------------
*/

void ScavTrap::printEnergyPoints()
{
	std::clog << "ScavTrap " << this->getName() << " has " << this->getEnergyPoints() << " energy points remaining." << std::endl;
}
void ScavTrap::attack(const std::string &target)
{
	if (this->getEnergyPoints() <= 0 || this->getHitPoints() <= 0)
	{
		std::cout << "ScavTrap " << this->getName() << " has no hit points or energy points to attack!" << std::endl;
		return;
	}
	else
	{
		std::cout << "ScavTrap " << this->getName() << " attacks " << target << ", causing " << this->getAttackDamage() << " points of damage!" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
		this->printEnergyPoints();
	}
}

void ScavTrap::takeDamage(unsigned int amount)
{
	if (amount >= this->getHitPoints())
		this->setHitPoints(0);
	else
		this->setHitPoints(this->getHitPoints() - amount);
	std::cout << "ScavTrap " << this->getName() << " takes " << amount << " points of damage!" << std::endl;
}

void ScavTrap::beRepaired(unsigned int amount)
{
	if (this->getEnergyPoints() <= 0 || this->getHitPoints() <= 0)
	{
		std::cout << "ScavTrap " << this->getName() << " has no hit points or energy points to repair!" << std::endl;
		return;
	}
	else
	{
		if (this->getHitPoints() + amount > 100)
			amount = 100 - this->getHitPoints();
		this->setHitPoints(this->getHitPoints() + amount);
		this->setEnergyPoints(this->getEnergyPoints() - 1);
		std::cout << "ScavTrap " << this->getName() << " is repaired " << amount << " points!" << std::endl;
		this->printEnergyPoints();
	}
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << getName() << " is now in Gate Keeper mode!" << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */