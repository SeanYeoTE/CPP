/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:52:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/20 16:38:03 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <iomanip>

class Contact {
	public:
		Contact();
		void set_firstname(std::string first_name);
		void set_lastname(std::string last_name);
		void set_nickname(std::string nickname);
		void set_phonenumber(std::string phone_number);
		std::string get_firstname() const;
		std::string get_lastname() const;
		std::string get_nickname() const;
		std::string get_phonenumber() const;
		void print_contact() const;
		// bool is_empty() const;
		
	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		
};

#endif
