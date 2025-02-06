/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:01:04 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/06 19:46:33 by agodeanu         ###   ########.fr       */
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
	std::cout << std::endl;
	clurp = clappy;
	std::cout << clurp << "\n";
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

	clapairy.beRepaired(1);
	clapairy.setHP(9);
	clapairy.setEP(10);
	clapairy.beRepaired(1);
	clapairy.beRepaired(1);

	clapairy.setHP(1);
	clapairy.takeDamage(1);
	clapairy.takeDamage(1);
	clapairy.setHP(1);
	clapairy.takeDamage(2);
	clapairy.beRepaired(1);
	std::string	attacker = "clurpixur";
	clapairy.attack(attacker);
	return (0);
}
