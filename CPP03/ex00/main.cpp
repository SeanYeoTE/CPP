/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:20:51 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/10 17:28:19 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap clapTrap("ClapTrap1");
    clapTrap.attack("target");
    clapTrap.takeDamage(5);
    clapTrap.beRepaired(2);

    // more tests
    ClapTrap clapTrap2("ClapTrap2");
    clapTrap2.attack("target2");
    clapTrap2.takeDamage(5);
    clapTrap2.beRepaired(2);
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");
    clapTrap2.attack("target3");

    clapTrap2.attack("target3");
    clapTrap2.beRepaired(2);
}
