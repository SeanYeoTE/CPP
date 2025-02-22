/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:45:33 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 15:52:38 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon) {
    return;
}

HumanA::~HumanA() {
    return;
}

void HumanA::attack() const {
    std::cout << this->_name << " attacks with his " << this->_weapon.getType() << std::endl;
}

