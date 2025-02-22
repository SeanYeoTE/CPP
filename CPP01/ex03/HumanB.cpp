/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:53:14 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 15:53:31 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
    return;
}

HumanB::~HumanB() {
    return;
}

void HumanB::attack() const {
    if (this->_weapon)
        std::cout << this->_name << " attacks with his " << this->_weapon->getType() << std::endl;
    else
        std::cout << this->_name << " has no weapon to attack with" << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) {
    this->_weapon = &weapon;
}
