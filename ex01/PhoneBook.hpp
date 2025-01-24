/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:21:10 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/24 14:00:52 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "Contact.hpp"
# include <iomanip>

class Phonebook {
	public:
		Phonebook();
		void add();
		void search() const;
		
	private:
		Contact contacts[8];
		int contact_count;
		int oldest_contact;
		void display_search_header() const;
		void display_contact_details(int index) const;
};

#endif
