/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:22:46 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 16:25:28 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp" 

class PhoneBook
{
	private:
		Contact	phonebook[8];
	public:
		PhoneBook();
		~PhoneBook();
		void	add_contact();
		Contact	search_contact();
};

#endif