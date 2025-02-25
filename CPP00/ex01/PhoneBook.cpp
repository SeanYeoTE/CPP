/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:20:35 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/25 12:34:52 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() {
    contact_count = 0;
    oldest_contact = 0;
}

static bool is_only_whitespace(const std::string &str) {
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {
        if (*it != ' ' && *it != '\t' && *it != '\n' && *it != '\v' && *it != '\f' && *it != '\r')
            return false;
    }
    return true;
}

static std::string get_input(const std::string &prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input))
        {
            std::cout << "Bad input." << std::endl;
            break;
        }
        if (!input.empty() && !is_only_whitespace(input))
            break;
        std::cout << "Field cannot be empty. Please try again." << std::endl;
    }
    return input;
}

void PhoneBook::add() {
    int index;
    if (contact_count < 8)
        index = contact_count;
    else
        index = oldest_contact;
    
    contacts[index].set_firstname(get_input("Enter first name: "));
    contacts[index].set_lastname(get_input("Enter last name: "));
    contacts[index].set_nickname(get_input("Enter nickname: "));
    contacts[index].set_phonenumber(get_input("Enter phone number: "));
    
    if (contact_count < 8)
        contact_count++;
    else
        oldest_contact = (oldest_contact + 1) % 8;
    
    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::display_search_header() const {
    std::cout << "|-------------------------------------------|" << std::endl;
    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
    std::cout << "|-------------------------------------------|" << std::endl;
}

void PhoneBook::display_contact_details(int index) const {
    std::cout << "\nContact Details:" << std::endl;
    std::cout << "First Name: " << contacts[index].get_firstname() << std::endl;
    std::cout << "Last Name: " << contacts[index].get_lastname() << std::endl;
    std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
    std::cout << "Phone Number: " << contacts[index].get_phonenumber() << std::endl;
    }

void PhoneBook::search() const {
    if (contact_count == 0) {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }
    display_search_header();
    for (int i = 0; i < contact_count; i++) {
        std::cout << "|" << std::left << std::setw(10)  << i;
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
            
        std::istringstream iss(input);
        if (!(iss >> index)) {
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        else {
            if (index >= 0 && index < contact_count) {
                display_contact_details(index);
                break;
            }
        }
        std::cout << "Invalid index. Please try again." << std::endl;
    }
}
