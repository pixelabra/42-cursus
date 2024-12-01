/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:21:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 16:38:18 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include "PhoneBook.hpp"

std::string	get_input()
{
	std::string	input;

	std::getline(std::cin, input);
	if (std::cin.eof())
	{
		std::cout << "EOF\n";
		exit(0);
	}
	
	return (input);
}

int	main()
{
	std::string	input;
	PhoneBook	ph_book;

	while (1)
	{
		
		input = get_input();
		if (input == "ADD")
			ph_book.add_contact();
		else if (input == "SEARCH")
			ph_book.search_contact();
		else if (input == "EXIT")
			ph_book.exit();
	}
	return (0);
}
