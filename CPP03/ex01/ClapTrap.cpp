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
	hitPoints -= amount;
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
		if (hitPoints + amount > 10)
			amount = 10 - hitPoints;
		hitPoints += amount;
		energyPoints--;
		std::cout << "ClapTrap " << name << " is repaired " << amount << " points!" << std::endl;
		printEnergyPoints();
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string ClapTrap::getName() const
{
	return name;
}

int ClapTrap::getHitPoints() const
{
	return hitPoints;
}

int ClapTrap::getEnergyPoints() const
{
	return energyPoints;
}

int ClapTrap::getAttackDamage() const
{
	return attackDamage;
}

/* ************************************************************************** */