/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:20:56 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 18:00:23 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA() {
	name = "Default HumanA";
	std::cout << name << " is born" << std::endl;
}

HumanA::HumanA(std::string newname, Weapon newweapon) {
	name = newname;
	weapon = newweapon;
}

HumanA::~HumanA() {
	std::cout << name << " died" << std::endl;
}

void	HumanA::attack() {
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}
