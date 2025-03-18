#include "../includes/ScavTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ScavTrap::ScavTrap() : ClapTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	setMaxHitPoints(100);  // Set max HP first
	setHitPoints(100);     // Then set current HP
	setEnergyPoints(50);   // Use setter method
	setAttackDamage(20);   // Use setter method
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "ScavTrap constructor called" << std::endl;
	setMaxHitPoints(100);  // Set max HP first
	setHitPoints(100);     // Then set current HP
	setEnergyPoints(50);   // Use setter method
	setAttackDamage(20);   // Use setter method
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
	// Copy the specific attributes if any
	setHitPoints(src.getHitPoints());
	setEnergyPoints(src.getEnergyPoints());
	setAttackDamage(src.getAttackDamage());
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << getName() << " destroyed." << std::endl;
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

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap assignment operator called" << std::endl;
	if (this != &other) // Check for self-assignment
	{
		ClapTrap::operator=(other); // Call base class assignment operator
	}
	return *this;
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

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << getName() << " is now in Gate Keeper mode!" << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
