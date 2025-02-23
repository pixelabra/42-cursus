/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:35:41 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/07 15:53:42 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	HP = default_HP;
	EP = default_EP;
	ATK = default_ATK;
	std::cout << "Default ScavTrap Constructor called for ScavTrap " << Name << ".\n\n";
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	std::cout << "Default name ScavTrap constructor called for ScavTrap " << Name << ".\n\n";
}

ScavTrap::ScavTrap(const ScavTrap& other): ClapTrap(other)
{
	std::cout << "Copy ScavTrap constructor called.\n\n";
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "Copy ScavTrap assignment overload:\n";
	std::cout << this->getName() << " becomes " << other.getName() << "\n\n";
	if (this == &other)
		return (*this);
	Name = other.Name;
	HP = other.HP;
	EP = other.EP;
	ATK = other.ATK;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << Name << " is destroyed.\n";
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << Name << " enters Gate Keeper mode.\n\n";
}

void	ScavTrap::attack(std::string& target)
{
	if (!HP)
	{
		std::cout << "ScavTrap " << Name << " cannot attack "<< target << ".\n";
		std::cout << "ScavTrap " << Name << " is dead. (oh no!)\n\n";
		return ;
	}
	if (EP)
	{
		EP--;
		std::cout << "ScavTrap " << Name << " attacks " << target << ", inflicting "
				<< ATK << " damage!";
		if (!ATK)
				std::cout << " (pretty useless!)";
		std::cout << "\n\n";
	}
	else
		std::cout << "ScavTrap " << Name << " has no energy to attack\n\n";
}
