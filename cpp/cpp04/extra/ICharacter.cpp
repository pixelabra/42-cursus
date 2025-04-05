/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:57:28 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 16:55:08 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICharacter.hpp"

ICharacter::ICharacter()
{
	std::cout << "ICharacter constructor summoned.\n";
	for (int i = 0; i < INV; i++)
		inventory[i] = NULL;
}

ICharacter::ICharacter(const ICharacter& other): name(other.name)
{
	std::cout << "ICharacter copy constructor summoned.\n";
	for (int i = 0; i < INV;i++)
	{
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
}

ICharacter::ICharacter(std::string _name): name(_name)
{
	std::cout << "ICharacter copy constructor summoned.\n";
}

ICharacter& ICharacter::operator=(const ICharacter& other)
{
	std::cout << "ICharacter assignment overlord.\n";
	if (this == &other)
		return (*this);
	name = other.name;
	for (int i = 0; i < INV;i++)
	{
		if (inventory[i])
			delete inventory[i];
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
	return (*this);
}

ICharacter::~ICharacter()
{
	std::cout << "ICharacter destructor summoned.\n";
	for (int i = 0; i < INV; i++)
	{
		if (inventory[i])
			delete inventory[i];
	}
}
