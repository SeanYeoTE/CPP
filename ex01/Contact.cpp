/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:53:10 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 16:53:53 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include <iostream>

void Contact::set_firstname(std::string first_name) {
	_first_name = first_name;
}

void Contact::set_lastname(std::string last_name) {
	_last_name = last_name;
}

void Contact::set_nickname(std::string nickname) {
	_nickname = nickname;
}

void Contact::set_login(std::string login) {
	_login = login;
}

void Contact::print_contact() {
	std::cout << "First Name: " << _first_name << std::endl;
	std::cout << "Last Name: " << _last_name << std::endl;
	std::cout << "Nickname: " << _nickname << std::endl;
	std::cout << "Login: " << _login << std::endl;
}

