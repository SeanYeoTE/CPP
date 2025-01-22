/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:20:35 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 18:03:18 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

void Phonebook::add() {
    if (contact_count == 8) {
        std::cout << "Phonebook is full. Cannot add more contacts." << std::endl;
        return;
    }
    contacts[contact_count].add();
    contact_count++;
}

void Phonebook::search() {
    for (i = 0; i < contact_count; i++) {
        contacts[i].print_contact();
    }
}