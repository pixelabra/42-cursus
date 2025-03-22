/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:06:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/22 16:57:13 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat default creation activated.\n";
	brain = new Brain();
}

Cat::Cat(const Cat& other): Animal("Cat")
{
	std::cout << "Cat copy constructors activated.\n";
	type = other.type;
	brain = new Brain(*other.brain);
}

Cat&	Cat::operator=(const Cat& other)
{
	std::cout << "Cat copy assignment overload activated.\n";
	if (this == &other)
		return (*this);
	Animal::operator=(other);
	if (brain)
		delete brain;
	brain = new Brain(*other.brain);
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat is no longer with us.\n";
	delete brain;
}

void	Cat::makeSound(void) const
{
	std::cout << "meow\n";
}

void	Cat::getIdeas(void) const
{
	if (brain)
		brain->getIdeas();
}

void	Cat::setIdea(int index, std::string message)
{
	if (brain && index >= 0 && index < 100)
		brain->setIdea(index, message);
}
