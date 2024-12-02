/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:49:16 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 20:25:55 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() {
	filled = 0;
}

PhoneBook::~PhoneBook() {}

void	PhoneBook::add_contact() {
	static int	index;
	
	if (index == 8)
		index = 0;
	std::cout << "First Name: ";
	contacts[index].setFirstName(get_input());
	std::cout << "Last Name: ";
	contacts[index].setLastName(get_input());
	std::cout << "Nickname: ";
	contacts[index].setNickname(get_input());
	std::cout << "Phone Number: ";
	contacts[index].setPhNumber(get_input_nbr());
	std::cout << "Darkest Secret: ";
	contacts[index].setSecret(get_input());
	if (filled < 8)
		filled++;
	index++;
}

std::string	trunc(std::string str)
{
	if (str.length() <= 10)
		return (str);
	str[9] = '.';
	str.resize(10);
	return (str);
}

void	PhoneBook::display_contacts() {
	if (filled == 0)
	{
		std::cout << "Phonebook empty\n";
		return ;
	}
	std::cout << "|     INDEX";
	std::cout << "|FIRST NAME";
	std::cout << "| LAST NAME";
	std::cout << "|  NICKNAME|\n";
	for (int i = 0; i < filled; i++)
	{
		std::cout << "|" << std::setw(10) << i + 1;
		std::cout << "|" << std::setw(10) << trunc(contacts[i].getFirstName());
		std::cout << "|" << std::setw(10) << trunc(contacts[i].getLastName());
		std::cout << "|" << std::setw(10) << trunc(contacts[i].getNickname());
		std::cout << "|\n";
	}
	std::cout << std::endl;
}

void	PhoneBook::select_contact() {
	std::string	input;
	int			input_nbr;

	if (filled == 0)
		return ;
	std::cout << "Select index of contact, or 0 to go back: ";
	input = get_input_nbr();
	input_nbr = std::atoi(input.c_str());
	if (input_nbr == 0)
		return ;
	if (input_nbr > 8 || input_nbr < 1 || input_nbr > filled) {
		std::cout << "Invalid index.\n";
		search_contact();
	}
	else
	{
		std::cout << "First Name: " << contacts[input_nbr - 1].getFirstName() << std::endl;
		std::cout << "Last Name: " << contacts[input_nbr - 1].getLastName() << std::endl;
		std::cout << "Nickname: " << contacts[input_nbr - 1].getNickname() << std::endl;
		std::cout << "Phone Number: " << contacts[input_nbr - 1].getPhNumber() << std::endl;
		std::cout << "Darkest Secret: " << contacts[input_nbr - 1].getSecret() << std::endl;
	}
}

void	PhoneBook::search_contact() {
	display_contacts();
	select_contact();
}
