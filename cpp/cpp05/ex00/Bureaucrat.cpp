/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:35:30 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 20:52:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("basic"), grade(150)
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " joined." << std::endl;
}

Bureaucrat::Bureaucrat(const std::string _name, int _grade): name(_name)
{
	if (_grade > 150) {
		throw GradeTooLowException();
	}
	if (_grade < 1) {
		throw GradeTooHighException();
	}
	std::cout << BOLD << MAGENTA << "[p_CONSTR]" << RESET << " ";
	grade = _grade;
	std::cout << name << "(" << grade << ")" << " joined." << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other): name("basic+"), grade(other.grade)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " joined." << std::endl;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this == &other) {
		return (*this);
	}
	std::cout << BOLD << BLACK << "[OVRLRD]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " --> ";
	std::cout << name << "(" << other.grade << ")" << std::endl;
	grade = other.grade;
	return (*this);
}

std::ostream&	operator<<(std::ostream& stream, const Bureaucrat& bcrat)
{
	stream << bcrat.getName() << "(" << bcrat.getGrade() << ")" << std::endl;
	return (stream);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " left." << std::endl;
}

const std::string&		Bureaucrat::getName() const { return (name); }
const int&				Bureaucrat::getGrade() const { return (grade); }

void	Bureaucrat::promote()
{
	if (grade <= 1) {
		std::cout << name << ": ";
		throw GradeTooHighException();
	}
	std::cout << BOLD << GREEN << "[PRMT]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " --> ";
	std::cout << name << "(" << --grade << ")" << std::endl;
}

void	Bureaucrat::demote()
{
	if (grade >= 150) {
		std::cout << name << ": ";
		throw GradeTooLowException();
	}
	std::cout << BOLD << CYAN << "[DMT]" << RESET << " ";
	std::cout << name << "(" << grade << ")" << " --> ";
	std::cout << name << "(" << ++grade << ")" << std::endl;
}

Bureaucrat::GradeTooHighException::GradeTooHighException():
	message("level higher than 1 not allowed.\n") {}
Bureaucrat::GradeTooLowException::GradeTooLowException():
	message("level lower than 150 not allowed.\n") {}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	std::cout << "\n---------------" << std::endl;
	std::cout << BOLD << CYAN << "[EXCPT]" << RESET << " ";
	return (message.c_str());
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	std::cout << "\n---------------" << std::endl;
	std::cout << BOLD << CYAN << "[EXCPT]" << RESET << " ";
	return (message.c_str());
}
