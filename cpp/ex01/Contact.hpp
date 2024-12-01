/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:23:21 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 19:02:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nick_name;
		std::string	phone_number;
		std::string	dark_secret;
	public:
		Contact();
		~Contact();
		void		setFirstName(std::string firstname);
		void		setLastName(std::string lastname);
		void		setNickname(std::string nickname);
		void		setPhNumber(std::string phnumber);
		void		setSecret(std::string secret);
		std::string	getFirstName();
		std::string	getLastName();
		std::string	getNickname();
		std::string	getPhNumber();
		std::string	getSecret();
};

#endif