/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:55:14 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 17:51:46 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "contact.hpp"
#include "phonebook.hpp"

int main() {
    Phonebook phonebook;
    std::string command;

    while (1) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);
        if (command == "EXIT") {
            break;
        } else if (command == "ADD") {
            Contact contact = create_contact();
            phonebook.add(contact);
        } else if (command == "SEARCH") {
            phonebook.search();
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
    return 0;
}