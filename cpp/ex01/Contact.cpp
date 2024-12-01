/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:32:52 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 16:14:59 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

Contact::~Contact() {}

void	Contact::setFirstName(std::string firstname) {
	first_name = firstname;
}

void	Contact::setLastName(std::string lastname) {
	last_name = lastname;
}

void	Contact::setNickame(std::string nickname) {
	nick_name = nickname;
}

void	Contact::setPhNumber(std::string phnumber) {
	phone_number = phnumber;
}

void	Contact::setSecret(std::string secret) {
	dark_secret = secret;
}

std::string	Contact::getFirstName() {
	return (first_name);
}

std::string	Contact::getLastName() {
	return (last_name);
}

std::string	Contact::getNickame() {
	return (nick_name);
}

std::string	Contact::getPhNumber() {
	return (phone_number);
}

std::string	Contact::getSecret() {
	return (dark_secret);
}
