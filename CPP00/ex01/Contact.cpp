/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:53:10 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/22 18:53:55 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

static std::string truncate(std::string str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

Contact::Contact()
{
	_first_name = "";
	_last_name = "";
	_nickname = "";
	_phone_number = "";
}

void Contact::set_firstname(std::string first_name)
{
	_first_name = first_name;
}

void Contact::set_lastname(std::string last_name)
{
	_last_name = last_name;
}

void Contact::set_nickname(std::string nickname)
{
	_nickname = nickname;
}

void Contact::set_phonenumber(std::string phone_number)
{
	_phone_number = phone_number;
}

std::string Contact::get_firstname() const
{
	return (_first_name);
}

std::string Contact::get_lastname() const
{
	return (_last_name);
}

std::string Contact::get_nickname() const
{
	return (_nickname);
}

std::string Contact::get_phonenumber() const
{
	return (_phone_number);
}

void Contact::print_contact() const
{
	std::cout << "|" << std::setw(10) << std::right << truncate(_first_name) << "|";
	std::cout << std::setw(10) << std::right << truncate(_last_name) << "|";
	std::cout << std::setw(10) << std::right << truncate(_nickname) << "|" << std::endl;
}
