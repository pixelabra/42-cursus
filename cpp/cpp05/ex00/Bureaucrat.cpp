/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:35:30 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/05 21:25:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
	std::cout << "Default bureaucrat activated." << std::endl;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this == &other)
		return (*this);
	grade = other.grade;
	return (*this);
}

std::stream&	Bureaucrat::operator<<(std::ostream& stream, const Bureaucrat& other)
{

}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureacratopocalypse" << name << "\n";
}

std::string	Bureaucrat::getName() const { return (name); }
int			Bureaucrat::getGrade() const { return (grade); }
