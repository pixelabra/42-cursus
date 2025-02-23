/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:06:18 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/07 19:20:17 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
	Name = "Droupy Wroupy";
	ClapTrap::Name += SFFX;
	HP = FragTrap::default_HP;
	EP = ScavTrap::default_EP;
	ATK = FragTrap::default_ATK;
	std::cout << "Default DiamondTrap constructor called for DiamondTrap "<< Name << ".\n\n";
}

DiamondTrap::DiamondTrap(std::string Name): ClapTrap(Name + SFFX), Name(Name)
{
	this->Name = Name;
	HP = FragTrap::default_HP;
	EP = ScavTrap::default_EP;
	ATK = FragTrap::default_ATK;
	std::cout << "Default name DiamondTrap constructor called for DiamondTrap " << Name << ".\n\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap& other):
		ClapTrap(other), ScavTrap(other), FragTrap(other), Name(other.Name)
{
	std::cout << "Copy DiamondTrap constructor called.\n\n";
}

DiamondTrap&	DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << "Copy DiamondTrap assignment overload:\n";
	std::cout << this->getName() << " becomes " << other.getName() << "\n\n";
	if (this == &other)
		return (*this);
	Name = other.Name;
	ClapTrap::operator=(other);
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << Name << " has concluded the call.\n";
}

void	DiamondTrap::attack(std::string& target)
{
	ScavTrap::attack(target);
}

std::string	DiamondTrap::getName(void) const { return (Name);}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "DiamondTrap Name is " << getName() << ".\n";
	std::cout << "DiamondTrap's ClapTrap Name is " << ClapTrap::getName() << ".\n";
}
