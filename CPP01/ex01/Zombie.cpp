/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:38:25 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 13:38:36 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {
    return;
}

Zombie::~Zombie() {
    return;
}

void Zombie::setName(std::string name) {
    this->_name = name;
}

void Zombie::announce() {
    std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}