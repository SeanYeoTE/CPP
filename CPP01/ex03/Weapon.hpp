/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:36:11 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 14:43:11 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon {
    public:
        Weapon(std::string type);
        ~Weapon();
        const std::string& getType() const;
        void setType(std::string type);
    private:
        std::string _type;
};

#endif