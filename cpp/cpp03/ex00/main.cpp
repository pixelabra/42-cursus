/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:01:04 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/28 02:49:52 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main()
{
	ClapTrap	clap;
	ClapTrap	clurp;
	ClapTrap	clappy("clappy");
	ClapTrap	clapairy(clurp);

	std::cout << clurp;	
	clurp = clappy;
	std::cout << clurp;
	std::cout << clap << "\n" << clappy << "\n";
	clurp.setName("clurp");
	std::cout << clurp << std::endl;

	std::cout << "ATTACK | DAMAGE | REPAIR TESTS" << "\n";
	clapairy.attack("cloupi wooopy");
	clapairy.attack("cloupi wooopy");
	std::cout << clapairy << std::endl;
	clapairy.setEP(1);
	std::cout << clapairy << std::endl;
	clapairy.attack("cloupi wooopy");
	clapairy.attack("cloupi wooopy");
	std::cout << clapairy << std::endl;
	return (0);
}
