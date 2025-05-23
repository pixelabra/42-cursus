/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:06:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/04 16:37:21 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Dog default creation activated.\n";
}

Dog::Dog(const Dog& other): Animal("Dog")
{
	std::cout << "Dog copy constructors activated.\n";
	type = other.type;
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Dog copy assignment overload activated.\n";
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog of type " << type << " is no longer with us.\n";
}

void	Dog::makeSound(void) const
{
	std::cout << "woofywoof\n";
}
