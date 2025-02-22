/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:39:40 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 14:40:14 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA {
    public:
        HumanA(std::string name, Weapon& weapon);
        ~HumanA();
        void attack() const;

    private:
        std::string _name;
        Weapon& _weapon;
};

#endif