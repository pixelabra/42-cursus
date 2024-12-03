/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:21:01 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/03 17:08:32 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string newname) {
	name = newname;
}

void	HumanB::attack() {
	if (!weapon)
		std::cout << name << " is unarmed" << std::endl;
	else
		std::cout << name << " attacks with " << weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &newweapon) {
	weapon = &newweapon;
}
