/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:21:10 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/22 17:34:42 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "contact.hpp"
# include <iomanip>

class Phonebook {
	public:
		Phonebook();
		void add();
		void search();
		int create(int contact_count, Contact contacts[8], std::string first_name, std::string last_name, std::string nickname, std::string login);
		
	private:
		Contact contacts[8];
		int contact_count;
};

#endif