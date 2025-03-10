#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{

public:
	ClapTrap(std::string name);
	ClapTrap(ClapTrap const &src);
	~ClapTrap();

	ClapTrap &operator=(ClapTrap const &rhs);

	void attack(const std::string &target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

private:
	std::string name;
	int hitPoints;
	int energyPoints;
	int attackDamage;
	void printEnergyPoints();
};

std::ostream &operator<<(std::ostream &o, ClapTrap const &i);

#endif /* ******************************************************** CLAPTRAP_H */