/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:01:04 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/07 19:21:07 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

// int	main()
// {
// 	FragTrap	frurp;
// 	FragTrap	frappy("frappy");
// 	FragTrap	frapairy(frurp);

// 	std::cout << frurp << std::endl;
// 	frurp = frappy;
// 	std::cout << frurp << "\n";
// 	frurp.setName("frurp");
// 	std::cout << frurp << std::endl;

// 	std::cout << "ATTACK | DAMAGE | REPAIR TESTS" << "\n";

// 	std::string	attacker = "frurpurpur";
// 	frapairy.attack(attacker);
// 	frapairy.attack(attacker);
// 	std::cout << frapairy << std::endl;
// 	frapairy.setEP(1);
// 	std::cout << frapairy << std::endl;
// 	frapairy.attack(attacker);
// 	frapairy.attack(attacker);
// 	std::cout << frapairy << std::endl;
// 	std::cout << "------------------\n\n";
// 	frapairy.beRepaired(1);
// 	frapairy.setHP(99);
// 	frapairy.setEP(10);
// 	frapairy.beRepaired(1);
// 	frapairy.beRepaired(1);
// 	std::cout << frapairy << std::endl;
// 	std::cout << "------------------\n\n";
// 	frapairy.setHP(1);
// 	frapairy.takeDamage(3);
// 	frapairy.beRepaired(1);
// 	attacker = "frurpixur";
// 	frapairy.attack(attacker);
// 	frapairy.highFivesGuys();
// 	return (0);
// }

int	main()
{
	DiamondTrap	diamondY;
	DiamondTrap	diamondX("horse");

	std::cout << diamondX << std::endl;
	std::cout << diamondY << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << diamondX.getName() << std::endl;
	std::cout << diamondY.getName() << std::endl;
	diamondY.whoAmI();
	diamondX.whoAmI();
	std::cout << std::endl;
	std::cout << std::endl;
	diamondY.setATK(10000);
	diamondX = diamondY;
	diamondX.whoAmI();
	diamondY.whoAmI();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << diamondX << std::endl;
	return (0);
}
