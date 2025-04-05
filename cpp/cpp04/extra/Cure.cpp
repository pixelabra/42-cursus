/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:46:23 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 15:34:02 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(): AMateria("cure")
{
	std::cout << "Cure constructor summoned.\n";
}

Cure::Cure(const Cure& other): AMateria(other.type)
{
	std::cout << "Cure copy constructor summoned.\n";
}

Cure& Cure::operator=(const Cure& other)
{
	std::cout << "Cure assignment overlord.\n";
	if (this == &other)
		return (*this);
	return (*this);
}

Cure::~Cure()
{
	std::cout << "Cure destructor summoned.\n";
}

AMateria* Cure::clone() const
{
	return (new Cure());
}

void use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at" << target.getName() <<  " *\n";
}