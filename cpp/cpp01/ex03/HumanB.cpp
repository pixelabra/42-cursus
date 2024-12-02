/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:21:01 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 18:11:10 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB() {
	name = "Default HumanB";
	std::cout << name << " is born" << std::endl;
}

HumanB::HumanB(std::string newname) {
	name = newname;
}

HumanB::~HumanB() {
	std::cout << name << " died" << std::endl;
}

void	HumanB::attack() {
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}
