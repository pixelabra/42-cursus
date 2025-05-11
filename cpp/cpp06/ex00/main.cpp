/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:18:26 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/11 20:22:32 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "Error: Expected number of arguments should be 2." << std::endl;
		return (1);
	}
	const std::string input = std::string(av[1]);
	ScalarConverter::convert(input);
	return (0);
}
