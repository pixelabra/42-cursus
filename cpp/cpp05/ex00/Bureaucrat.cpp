/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:35:30 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/06 19:30:40 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("basic brrcrat"), grade(150)
{
	std::cout << "Basic constructor brrcrat activated." << std::endl;
}

Bureaucrat::Bureaucrat(const std::string _name, int _grade)
{
	std::cout << "Level brrcrat activated." << std::endl;
	if (_grade > 150)
		throw GradeTooLowException();
	if (_grade < 1)
		throw GradeTooHighException();
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this == &other)
		return (*this);
	grade = other.grade;
	return (*this);
}

std::ostream&	operator<<(std::ostream& stream, const Bureaucrat& bcrat)
{
	std::cout << bcrat.getName() << ", bureaucrat grade " << bcrat.getGrade() << std::endl;
	return (stream);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Brrcratopocalypse: " << name << " at grade " << grade << "\n";
}

const std::string&		Bureaucrat::getName() const { return (name); }
const int&				Bureaucrat::getGrade() const { return (grade); }

void	Bureaucrat::promote()
{
	if (grade <= 1)
		throw GradeTooHighException();
	grade--;
}

void	Bureaucrat::demote()
{
	if (grade >= 150)
		throw GradeTooLowException();
	grade++;
}
