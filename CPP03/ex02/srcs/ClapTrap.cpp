#include "ClapTrap.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ClapTrap::ClapTrap(std::string name)
{
	std::cout << "ClapTrap constructor called" << std::endl;
	this->name = name;
	maxHitPoints = 10;
	hitPoints = maxHitPoints;
	energyPoints = 10;
	attackDamage = 0;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	name = src.name;
	maxHitPoints = src.maxHitPoints;
	hitPoints = src.hitPoints;
	energyPoints = src.energyPoints;
	attackDamage = src.attackDamage;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << name << " destroyed." << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, ClapTrap const &i)
{
	o << "ClapTrap " << i.getName() << ":" << std::endl;
	o << "Hit Points: " << i.getHitPoints() << std::endl;
	o << "Energy Points: " << i.getEnergyPoints() << std::endl;
	o << "Attack Damage: " << i.getAttackDamage();
	return o;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &rhs)
{
	std::cout << "ClapTrap assignment operator called" << std::endl;
	if (this != &rhs) // Check for self-assignment
	{
		this->name = rhs.name;
		this->maxHitPoints = rhs.maxHitPoints;
		this->hitPoints = rhs.hitPoints;
		this->energyPoints = rhs.energyPoints;
		this->attackDamage = rhs.attackDamage;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void ClapTrap::printEnergyPoints()
{
	std::cout << "ClapTrap " << name << " has " << getEnergyPoints() << " energy points remaining." << std::endl;
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
	if (amount >= getHitPoints()) // Check if damage exceeds current hit points
		hitPoints = 0;			  // Set hit points to zero if damage exceeds
	else
		hitPoints -= amount; // Otherwise, reduce hit points
	std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (energyPoints <= 0 || hitPoints <= 0)
	{
		std::cout << "ClapTrap " << name << " has no hit points or energy points to repair!" << std::endl;
		return;
	}
	else
	{
		if (hitPoints + amount > maxHitPoints)
			amount = maxHitPoints - hitPoints;
		hitPoints += amount;
		energyPoints--;
		std::cout << "ClapTrap " << name << " is repaired " << amount << " points!" << std::endl;
		printEnergyPoints();
	}
}

void ClapTrap::setHitPoints(unsigned int points)
{
	hitPoints = points;
	maxHitPoints = points;
}

void ClapTrap::setEnergyPoints(unsigned int points)
{
	energyPoints = points;
}

void ClapTrap::setAttackDamage(unsigned int damage)
{
	attackDamage = damage;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string ClapTrap::getName() const
{
	return name;
}

unsigned int ClapTrap::getHitPoints() const
{
	return hitPoints;
}

unsigned int ClapTrap::getEnergyPoints() const
{
	return energyPoints;
}

unsigned int ClapTrap::getAttackDamage() const
{
	return attackDamage;
}

/* ************************************************************************** */
