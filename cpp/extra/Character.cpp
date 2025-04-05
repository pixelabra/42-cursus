/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:52:33 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/05 19:18:02 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	std::cout << "Character constructor summoned.\n";
}

Character::Character(const Character& other)
{
	std::cout << "Character copy constructor summoned.\n";

}

Character& Character::operator=(const Character& other)
{
	std::cout << "ICharacter assignment overlord.\n";
}

Character::~Character()
{
	std::cout << "ICharacter destructor summoned.\n";
}

const std::string&	Character::getName() const { return (name); }

void	Character::equip(AMateria *m)
{
	for (int i = 0; i < INV; i++)
	{
		if (!inventory[i])
		{
			inventory[i] = m;
			break ;
		}
	}
}

void	Character::unequip(int idx)
{
	if (idx >=0 && idx <=4 && inventory[idx])
		inventory[idx] = NULL;
}
