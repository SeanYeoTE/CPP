/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:20:35 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/24 14:19:00 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

Phonebook::Phonebook() {
    contact_count = 0;
    oldest_contact = 0;
}

static std::string get_input(const std::string &prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty())
            break;
        std::cout << "Field cannot be empty. Please try again." << std::endl;
    }
    return input;
}

void Phonebook::add() {
    int index;
    if (contact_count < 8)
        index = contact_count;
    else
        index = oldest_contact;
    
    contacts[index].set_firstname(get_input("Enter first name: "));
    contacts[index].set_lastname(get_input("Enter last name: "));
    contacts[index].set_nickname(get_input("Enter nickname: "));
    contacts[index].set_phonenumber(get_input("Enter phone number: "));
    contacts[index].set_darkest_secret(get_input("Enter darkest secret: "));
    
    if (contact_count < 8)
        contact_count++;
    else
        oldest_contact = (oldest_contact + 1) % 8;
    
    std::cout << "Contact added successfully!" << std::endl;
}

void Phonebook::display_search_header() const {
    std::cout << "|-------------------------------------------|" << std::endl;
    std::cout << "|     Index|First Name| Last Name| Nickname |" << std::endl;
    std::cout << "|-------------------------------------------|" << std::endl;
}

void Phonebook::display_contact_details(int index) const {
    std::cout << "\nContact Details:" << std::endl;
    std::cout << "First Name: " << contacts[index].get_firstname() << std::endl;
    std::cout << "Last Name: " << contacts[index].get_lastname() << std::endl;
    std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
    std::cout << "Phone Number: " << contacts[index].get_phonenumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[index].get_darkest_secret() << std::endl;
}

void Phonebook::search() const {
    if (contact_count == 0) {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }

    display_search_header();
    for (int i = 0; i < contact_count; i++) {
        std::cout << "|" << std::setw(10) << i;
        contacts[i].print_contact();
    }
    std::cout << "|-------------------------------------------|" << std::endl;

    std::string input;
    int index;
    while (true) {
        std::cout << "\nEnter the index of the contact to display (or 'q' to quit): ";
        std::getline(std::cin, input);
        
        if (input == "q")
            return;
            
        try {
            index = std::stoi(input);
            if (index >= 0 && index < contact_count) {
                display_contact_details(index);
                break;
            }
        } catch (...) {}
        
        std::cout << "Invalid index. Please try again." << std::endl;
    }
}
