/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:36:49 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 15:47:14 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) {
}

Weapon::~Weapon() {
    return;
}

const std::string& Weapon::getType() const {
    return this->_type;
}

void Weapon::setType(std::string type) {
    this->_type = type;
}