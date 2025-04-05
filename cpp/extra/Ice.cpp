/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:41:21 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 15:34:24 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(): AMateria("ice") 
{
	std::cout << "Ice constructor summoned.\n";
}

Ice::Ice(const Ice& other): AMateria(other.type)
{
	std::cout << "Ice copy constructor summoned.\n";
}

Ice& Ice::operator=(const Ice& other)
{
	std::cout << "Ice assignment overlord.\n";
	if (this == &other)
		return (*this);
	return (*this);
}

Ice::~Ice()
{
	std::cout << "Ice destructor summoned.\n";
}

AMateria* Ice::clone() const
{
	return (new Ice());
}

void use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() <<  "'s wounds *\n";
}
