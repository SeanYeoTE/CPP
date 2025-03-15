#include "FragTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "FragTrap constructor called" << std::endl;
	setHitPoints(100);	  // Use setter method
	setEnergyPoints(100); // Use setter method
	setAttackDamage(30);  // Use setter method
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
	// Copy the specific attributes if any
	setHitPoints(src.getHitPoints());
	setEnergyPoints(src.getEnergyPoints());
	setAttackDamage(src.getAttackDamage());
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << getName() << " destroyed." << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
std::ostream &operator<<(std::ostream &o, FragTrap const &i)
{
	o << "FragTrap " << i.getName() << ":" << std::endl;
	o << "Hit Points: " << i.getHitPoints() << std::endl;
	o << "Energy Points: " << i.getEnergyPoints() << std::endl;
	o << "Attack Damage: " << i.getAttackDamage();
	return o;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	std::cout << "FragTrap assignment operator called" << std::endl;
	if (this != &other) // Check for self-assignment
	{
		ClapTrap::operator=(other); // Call base class assignment operator
	}
	return *this;
}
/*
** --------------------------------- METHODS ----------------------------------
*/

void FragTrap::printEnergyPoints()
{
	std::cout << "FragTrap " << this->getName() << " has " << this->getEnergyPoints() << " energy points remaining." << std::endl;
}

void FragTrap::attack(const std::string &target)
{
	if (this->getEnergyPoints() <= 0 || this->getHitPoints() <= 0)
	{
		std::cout << "FragTrap " << this->getName() << " has no hit points or energy points to attack!" << std::endl;
		return;
	}
	else
	{
		std::cout << "FragTrap " << this->getName() << " attacks " << target << ", causing " << this->getAttackDamage() << " points of damage!" << std::endl;
		this->setEnergyPoints(this->getEnergyPoints() - 1);
		this->printEnergyPoints();
	}
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << getName() << " requests a positive high five!" << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
