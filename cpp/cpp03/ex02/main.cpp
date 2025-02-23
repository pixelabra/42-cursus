/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:01:04 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/06 20:04:19 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int	main()
{
	FragTrap	frurp;
	FragTrap	frappy("frappy");
	FragTrap	frapairy(frurp);

	std::cout << frurp << std::endl;
	frurp = frappy;
	std::cout << frurp << "\n";
	frurp.setName("frurp");
	std::cout << frurp << std::endl;

	std::cout << "ATTACK | DAMAGE | REPAIR TESTS" << "\n";

	std::string	attacker = "frurpurpur";
	frapairy.attack(attacker);
	frapairy.attack(attacker);
	std::cout << frapairy << std::endl;
	frapairy.setEP(1);
	std::cout << frapairy << std::endl;
	frapairy.attack(attacker);
	frapairy.attack(attacker);
	std::cout << frapairy << std::endl;
	std::cout << "------------------\n\n";
	frapairy.beRepaired(1);
	frapairy.setHP(99);
	frapairy.setEP(10);
	frapairy.beRepaired(1);
	frapairy.beRepaired(1);
	std::cout << frapairy << std::endl;
	std::cout << "------------------\n\n";
	frapairy.setHP(1);
	frapairy.takeDamage(3);
	frapairy.beRepaired(1);
	attacker = "frurpixur";
	frapairy.attack(attacker);
	frapairy.highFivesGuys();
	return (0);
}
