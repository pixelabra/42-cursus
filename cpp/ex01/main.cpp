/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:21:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/01 00:04:25 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>

std::string	get_input()
{
	std::string	input;

	std::getline(std::cin, input);
	if (std::cin.eof())
	
	return (input);
}

int	main()
{
	std::string	input;

	// std::cin >> input;
	while (1)
	{
		std::getline(std::cin, input);
		if (std::cin.eof())
			break ;
		if (input == "EXIT")
			break ;
	}
	// if (input == "ADD")

	// if (input == "SEARCH")
	// if (input == "EXIT")
	// 	std::cout << "NOT POSSIBLE\n";
	return (0);
}
