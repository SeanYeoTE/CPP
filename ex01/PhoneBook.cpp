/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:20:35 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 17:35:18 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
int Phonebook::create(int contact_count, Contact contacts[8], std::string first_name, std::string last_name, std::string nickname, std::string login);
    contact_count =  0;
    for (int i = 0; i < 8; i++) {
        contacts[i].set_firstname("");
        contacts[i].set_lastname("");
        contacts[i].set_nickname("");
        contacts[i].set_login("");
    }
}

void Phonebook::add() {
    if (contact_count == 8) {
        std::cout << "Phonebook is full. Cannot add more contacts." << std::endl;
        return;
    }
    contacts[contact_count].add();
    contact_count++;
}

void Phonebook::search() {
    
}