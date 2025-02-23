/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:34:52 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/07 15:53:09 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
	HP = default_HP;
	EP = default_EP;
	ATK = default_ATK;
	std::cout << "Default FragTrap constructor called for FragTrap "<< Name << ".\n\n";
}

FragTrap::FragTrap(std::string name): ClapTrap(name)
{
	HP = default_HP;
	EP = default_EP;
	ATK = default_ATK;
	std::cout << "Default name FragTrap constructor called for FragTrap " << Name << ".\n\n";
}

FragTrap::FragTrap(const FragTrap& other): ClapTrap(other)
{
	HP = default_HP;
	EP = default_EP;
	ATK = default_ATK;
	std::cout << "Copy FragTrap constructor called.\n\n";
}

FragTrap&	FragTrap::operator=(const FragTrap& other)
{
	std::cout << "Copy FragTrap assignment overload:\n";
	std::cout << this->getName() << " becomes " << other.getName() << "\n\n";
	if (this == &other)
		return (*this);
	Name = other.Name;
	HP = other.HP;
	EP = other.EP;
	ATK = other.ATK;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << Name << " has concluded the call.\n";
}

void	FragTrap::highFivesGuys()
{
	std::cout <<"FragTrap " << Name << " says hello!\n";
}
