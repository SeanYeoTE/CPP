/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:09 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 14:44:32 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB {
    public:
        HumanB(std::string name);
        ~HumanB();
        void attack() const;
        void setWeapon(Weapon& weapon);

    private:
        std::string _name;
        Weapon* _weapon;
};

#endif