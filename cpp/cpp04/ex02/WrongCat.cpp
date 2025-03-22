/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:06:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/02 20:05:21 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat default creation activated.\n";
}

WrongCat::WrongCat(const WrongCat& other): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat copy constructors activated.\n";
	type = other.type;
}

WrongCat&	WrongCat::operator=(const WrongCat& other)
{
	std::cout << "WrongCat copy assignment overload activated.\n";
	if (this == &other)
		return (*this);
	WrongAnimal::operator=(other);
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat is no longer with us.\n";
}

void	WrongCat::makeSound(void) const
{
	std::cout << "meow\n";
}
