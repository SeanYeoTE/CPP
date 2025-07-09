#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{

public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap &other);

	ScavTrap &operator=(const ScavTrap &other);
	~ScavTrap(void);
	void printEnergyPoints();

	void attack(const std::string &target);
	void guardGate();
};

std::ostream &operator<<(std::ostream &o, ScavTrap const &i);

#endif /* ******************************************************** SCAVTRAP_H */
