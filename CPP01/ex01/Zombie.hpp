/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:37:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 13:39:13 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie {

    public:
        Zombie();
        ~Zombie();
        void setName(std::string name);
        void announce();
    private:
        std::string _name;
};

Zombie* zombieHorde(int N, std::string name);

#endif