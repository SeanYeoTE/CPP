#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{

public:
	ScavTrap(const std::string &name) : ClapTrap(name) {}

	void guardGate();

private:
};

#endif /* ******************************************************** SCAVTRAP_H */