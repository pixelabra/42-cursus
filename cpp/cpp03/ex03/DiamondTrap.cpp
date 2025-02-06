/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:06:18 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/06 20:32:15 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	std::cout << "Default DiamondTrap constructor called for DiamondTrap "<< Name << ".\n\n";
}

// DiamondTrap::DiamondTrap(std::string name): ClapTrap(name)
// {
// 	std::cout << "Default name DiamondTrap constructor called for DiamondTrap " << Name << ".\n\n";
// }

// DiamondTrap::DiamondTrap(const DiamondTrap& other): ClapTrap(other)
// {
// 	std::cout << "Copy DiamondTrap constructor called.\n\n";
// }

// DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& other)
// {
// 	std::cout << "Copy DiamondTrap assignment overload:\n";
// 	std::cout << this->getName() << " becomes " << other.getName() << "\n\n";
// 	if (this == &other)
// 		return (*this);
// 	Name = other.Name;
// 	HP = other.HP;
// 	EP = other.EP;
// 	ATK = other.ATK;
// 	return (*this);
// }

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << Name << " has concluded the call.\n";
}

void	DiamondTrap::attack(std::string& target)
{
	ScavTrap::attack(target);
}