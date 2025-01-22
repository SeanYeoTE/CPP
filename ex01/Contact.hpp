/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:52:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 16:53:39 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <iomanip>

class Contact {
	public:
		void set_firstname(std::string first_name);
		void set_lastname(std::string last_name);
		void set_nickname(std::string nickname);
		void set_login(std::string login);
		void print_contact();
		
	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _login;
		
};

#endif