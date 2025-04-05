/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:25:51 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 15:16:33 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(): type("default")
{
	std::cout << "AMateria constructor summoned.\n";
}

AMateria::AMateria(std::string const &_type): type(_type)
{
	std::cout << "AMateria type constructor summoned.\n";
}

AMateria::AMateria(const AMateria& other): type(other.type)
{
	std::cout << "AMateria copy constructor summoned.\n";
}

AMateria& AMateria::operator=(const AMateria& other)
{
	std::cout << "AMateria assignment overlord.\n";
	if (this == &other)
		return (*this);
	type = other.type;
	return (*this);
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor summoned.\n";
}

std::string const &AMateria::getType() const { return (type);}

void use(ICharacter& target)
{
	std::cout << "* not clear what this is doing *\n";
}
