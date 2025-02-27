/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:28:05 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/27 16:44:57 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>
#include <string>


class Harl
{
    public:
        Harl();
        ~Harl();
        void complain(std::string level);

    private:
        void debug();
        void info();
        void warning();
        void error();
        
};

#endif