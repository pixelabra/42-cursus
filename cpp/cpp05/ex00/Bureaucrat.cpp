/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:35:30 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/10 01:27:33 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("basic brrcrat"), grade(150)
{
	std::cout << "Basic constructor brrcrat activated." << std::endl;
}

Bureaucrat::Bureaucrat(const std::string _name, int _grade): name(_name)
{
	std::cout << "Level brrcrat activated." << std::endl;
	if (_grade > 150)
		throw GradeTooLowException();
	if (_grade < 1)
		throw GradeTooHighException();
	grade = _grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
{
	std::cout << "Copy constr. brrcrat activated." << std::endl;
	grade = other.grade;
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
	stream << bcrat.getName() << ", bureaucrat grade " << bcrat.getGrade() << std::endl;
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

Bureaucrat::GradeTooHighException::GradeTooHighException():
	message("Brrcrat already CEO, cannot have level higher than 1.\n") {}
Bureaucrat::GradeTooLowException::GradeTooLowException():
	message("Brrcrat already entry level, cannot have level lower than 150.\n") {}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return (message.c_str());
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return (message.c_str());
}
