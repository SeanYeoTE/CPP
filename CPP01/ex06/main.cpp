/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:55:42 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/27 17:08:58 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv)
{
    Harl harl;
    if (argc != 2)
    {
        std::cout << "Usage: ./harlFilter <level>" << std::endl;
        return (1);
    }
    harl.complain(argv[1]);
    return (0);
}
