/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:08:33 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/15 23:24:42 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int ac, char **av)
{
	Harl	harl;

	if (ac != 2)
	{
		std::cout << "Program requires one argument!\n";
		return (1);
	}
	harl.complain(av[1]);
	return (0);
}
