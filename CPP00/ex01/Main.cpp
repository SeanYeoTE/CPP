/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:55:14 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/21 18:15:06 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iostream>

int	main(void)
{
	PhoneBook	phonebook;

	std::string command;
	std::cout << "Welcome to PhoneBook!" << std::endl;
	std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
	while (true)
	{
		std::cout << "\nEnter a command: ";
		if (!std::getline(std::cin, command))
		{
        	std::cout << "\nEOF detected. Exiting..." << std::endl;
			break ;
        }
        if (command == "EXIT")
        {
			std::cout << "Goodbye!" << std::endl;
			break ;
        }
        else if (command == "ADD")
			phonebook.add();
		else if (command == "SEARCH")
			phonebook.search();
		else
			std::cout << "Invalid command. Available commands: ADD, SEARCH, EXIT" << std::endl;
	}
	return (0);
}
