/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:06:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/04 16:08:15 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat default creation activated.\n";
}

Cat::Cat(const Cat& other): Animal("Cat")
{
	std::cout << "Cat copy constructors activated.\n";
	type = other.type;
}

Cat&	Cat::operator=(const Cat& other)
{
	std::cout << "Cat copy assignment overload activated.\n";
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat of type " << type << " is no longer with us.\n";
}

void	Cat::makeSound(void) const
{
	std::cout << "meowpurr\n";
}
