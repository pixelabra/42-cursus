/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:06:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/04 13:36:42 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Dog default creation activated.\n";
	brain = new Brain();
}

Dog::Dog(const Dog& other): Animal("Dog")
{
	std::cout << "Dog copy constructors activated.\n";
	type = other.type;
	brain = new Brain();
	// for (int i = 0; i < 100; i++)
	// 	brain.ideas[i] = other.brain.ideas[i];
}

Dog&	Dog::operator=(const Dog& other)
{
	std::cout << "Dog copy assignment overload activated.\n";
	if (this == &other)
		return (*this);
	Animal::operator=(other);
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog is no longer with us.\n";
	delete brain;
}

void	Dog::makeSound(void) const
{
	std::cout << "woof\n";
}
