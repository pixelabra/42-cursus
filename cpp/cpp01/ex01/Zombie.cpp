/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:55:45 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 15:59:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {
	name = "Default Zombie";
	std::cout << name << " created.\n";
}

Zombie::Zombie(std::string newname) {
	name = newname;
	std::cout << name << " created.\n";
}

Zombie::~Zombie() {
	std::cout << name << " destroyed.\n";
}

void	Zombie::announce(void) {
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

void	Zombie::setName(std::string zombie_name)
{
	name = zombie_name;
}
