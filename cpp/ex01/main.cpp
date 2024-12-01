/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:21:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 18:46:39 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	check_empty_input(std::string input)
{
	if (std::cin.eof())
	{
		std::cout << "EOF\n";
		exit(0);
	}
	if (input == "")
	{
		std::cout << "Input must not be empty\n";
		return (1);
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isspace(input[i]))
			return (0);
	}
	std::cout << "Input must not be empty\n";
	return (1);
}

std::string	get_input_nbr()
{
	std::string	input;

	std::getline(std::cin, input);
	if (check_empty_input(input))
		return (get_input_nbr());
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
		{
			std::cout << "Input must contain only digits\n";
			return (get_input_nbr());
		}
	}
	return (input);
}

std::string	get_input()
{
	std::string	input;

	std::getline(std::cin, input);
	if (check_empty_input(input))
		return (get_input());
	return (input);
}

int	main()
{
	std::string	input;
	PhoneBook	ph_book;

	while (1)
	{
		std::cout << "Please input one of the following commanda: ADD, SEARCH, EXIT:\n";
		input = get_input();
		if (input == "ADD")
			ph_book.add_contact();
		else if (input == "SEARCH")
			ph_book.search_contact();
		else if (input == "EXIT")
			break ;
	}
	return (0);
}
