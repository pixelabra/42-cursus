/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:10:35 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/28 00:55:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): Health(10), Energy(10), Damage(0)
{
	Name = "Basic";
	std::cout << "Default constructor called for ClapTrap" << Name << "\n";
}

ClapTrap::ClapTrap(std::string name): Health(10), Energy(10), Damage(0)
{
	Name = name;
	std::cout << "Default constructor called for ClapTrap" << Name << "\n";
}

ClapTrap::ClapTrap(const ClapTrap& other): Name(other.Name), Health(other.Health),
	Energy(other.Energy), Damage(other.Energy)
{
	std::cout << "Copy constructor called\n";
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destroyed\n";
}

void	ClapTrap::attack(const std::string& target)
{
	
	std::cout << "ClapTrap " << Name << " attacks " << target << ", causing "
			<< Damage << " points of damage!\n";
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	Damage++;
	std::cout << "ClapTrap " << Name << " takes " << amount << " points of damage!\n";
	std::cout << "ClapTrap" << Name << "'s health is " << Health << "health.\n\n";
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	Damage--;
	std::cout << "ClapTrap " << Name << " repaired " << amount << "\n";
	std::cout << "ClapTrap" << Name << "'s health is " << Health << "health.\n\n";
}
