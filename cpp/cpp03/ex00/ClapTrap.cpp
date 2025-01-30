/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:10:35 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/31 02:14:03 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): HP(10), EP(10), ATK(0)
{
	Name = "Oupi Goupi";
	std::cout << "Default constructor called for ClapTrap " << Name << ".\n";
}

ClapTrap::ClapTrap(std::string name): HP(10), EP(10), ATK(0)
{
	Name = name;
	std::cout << "Default name constructor called for ClapTrap " << Name << "\n";
}

ClapTrap::ClapTrap(const ClapTrap& other): Name(other.Name), HP(other.HP),
	EP(other.EP), ATK(other.ATK)
{
	std::cout << "Copy constructor called\n\n";
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "Copy assignment constructor called\n";
	std::cout << this->getName() << " becomes " << other.getName() << "\n\n";
	if (this == &other)
		return (*this);
	Name = other.getName();
	HP = other.HP;
	EP = other.EP;
	ATK = other.ATK;
	return (*this);
}

std::string		ClapTrap::getName(void) const { return (Name);}
unsigned int	ClapTrap::getHP(void) const { return (HP);}
unsigned int	ClapTrap::getEP(void) const { return (EP);}
unsigned int	ClapTrap::getATK(void) const { return (ATK);}
void			ClapTrap::setName(std::string name) {Name = name;}
void			ClapTrap::setHP(unsigned int hp) {HP = hp;}
void			ClapTrap::setEP(unsigned int ep) {EP = ep;}
void			ClapTrap::setATK(unsigned int atk) {ATK = atk;}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << Name << " Destroyed\n";
}

void	ClapTrap::attack(const std::string& target)
{
	if (!HP)
	{
		std::cout << "ClapTrap " << Name << " cannot attack "<< target << ".\n";
		std::cout << "ClapTrap " << Name << " is dead. (oh no!)\n\n";
		return ;
	}
	if (EP)
	{
		EP--;
		std::cout << "ClapTrap " << Name << " attacks " << target << ", inflicting "
				<< ATK << " damage!";
		if (!ATK)
			std::cout << " (pretty useless!)";
		std::cout << "\n\n";
	}
	else
		std::cout << "ClapTrap " << Name << " has no energy to attack\n\n";
}	

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (HP)
	{
		HP--;
		std::cout << "ClapTrap " << Name << " takes " << amount << " points of damage!\n";
		std::cout << "ClapTrap " << Name << "'s HP is " << HP << "HP.\n\n";
		if (!HP)
			std::cout << "ClapTrap " << Name << " fully died (oh no!)\n\n";
	}
	else
		std::cout << "ClapTrap " << Name << " is already dead. It cannot take more damage.\n\n";
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (!HP)
	{
		std::cout << "ClapTrap " << Name << " cannot be repaired.\n";
		std::cout << "ClapTrap " << Name << " is dead. (oh no!)\n\n";
		return ;
	}
	if (EP)
	{
		if (HP < 10)
		{
			HP++;
			EP--;
			std::cout << "ClapTrap " << Name << " repaired " << amount << "\n";
			std::cout << "ClapTrap " << Name << "'s HP is " << HP << "HP.\n\n";
		}
		else
			std::cout << "ClapTrap " << Name << " tried to repair itself but it already reached maximum health.\n\n";
	}
	else
		std::cout << "ClapTrap " << Name << " does not have energy to repair itself.\n\n";
}

std::ostream&	operator<<(std::ostream& stream, const ClapTrap& other)
{
	std::cout << "ClapTrap " << other.getName() << std::endl;
	std::cout << "HP: " << other.getHP() << std::endl;
	std::cout << "EP: " << other.getEP() << std::endl;
	std::cout << "ATK: " << other.getATK() << std::endl;
	return (stream);
}
