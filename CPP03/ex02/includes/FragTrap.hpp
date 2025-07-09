#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{

public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &other);

	FragTrap &operator=(const FragTrap &other);
	~FragTrap(void);
	void printEnergyPoints();

	void attack(const std::string &target);
	void highFivesGuys(void);
};

std::ostream &operator<<(std::ostream &o, FragTrap const &i);

#endif /* ******************************************************** FRAGTRAP_H */
