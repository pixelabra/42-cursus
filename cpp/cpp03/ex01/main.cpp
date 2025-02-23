/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:01:04 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/06 19:46:21 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main()
{
	ScavTrap	clurp;
	ScavTrap	clappy("clappy");
	ScavTrap	clapairy(clurp);

	std::cout << clurp << std::endl;
	clurp = clappy;
	std::cout << clurp << "\n";
	clurp.setName("clurp");
	std::cout << clurp << std::endl;

	std::cout << "ATTACK | DAMAGE | REPAIR TESTS" << "\n";

	std::string	attacker = "cloupi wooopy";
	clapairy.attack(attacker);
	clapairy.attack(attacker);
	std::cout << clapairy << std::endl;
	clapairy.setEP(1);
	std::cout << clapairy << std::endl;
	clapairy.attack(attacker);
	clapairy.attack(attacker);
	std::cout << clapairy << std::endl;
	std::cout << "------------------\n\n";
	clapairy.beRepaired(1);
	clapairy.setHP(99);
	clapairy.setEP(10);
	clapairy.beRepaired(1);
	clapairy.beRepaired(1);
	std::cout << clapairy << std::endl;
	std::cout << "------------------\n\n";
	clapairy.setHP(1);
	clapairy.takeDamage(3);
	clapairy.beRepaired(1);
	attacker = "scurpixur";
	clapairy.attack(attacker);
	clapairy.guardGate();
	return (0);
}
