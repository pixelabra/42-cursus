/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:19:17 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/22 16:57:18 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default creation activated\n";
	for (int i = 0; i < 100; i++)
		ideas[i] = "(bwank)";
}

Brain::Brain(const Brain& other)
{
	std::cout << "Brain copy constructor activated\n";
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
}

Brain& Brain::operator=(const Brain& other)
{
	if (this == &other)
		return (*this);
	for (int i = 0; i < 100; i++)
		ideas[i] = other.ideas[i];
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain is no longer with us.\n";
}

void	Brain::getIdeas(void) const
{
	for (int i = 0; i < 100; i++)
		std::cout << ideas[i] << std::endl;
}

void	Brain::setIdea(int index, std::string message)
{
	if (index >= 0 && index < 100)
		ideas[index] = message;
}
