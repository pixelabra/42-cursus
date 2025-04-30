/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:01:55 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/30 19:39:08 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(): minSign(150), minExec(150), name("blank"), isSigned(false)
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " created." << std::endl;
}

Form::Form(const std::string _name, const int _minSign, const int _minExec):
name(_name), minSign(_minSign), minExec(_minExec)
{
	std::cout << BOLD << MAGENTA << "[p_CONSTR]" << RESET << " ";
	if (minSign > 150 || minExec > 150) {
		std::cout << name << ": ";
		throw GradeTooLowException();
	}
	if (minSign < 1 || minExec > 1) {
		std::cout << name << ": ";
		throw GradeTooHighException();
	}
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " created." << std::endl;
}

Form::Form(const Form& other): minSign(other.minSign),
	minExec(other.minExec), name(other.name), isSigned(other.isSigned)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " copied." << std::endl;
}

Form&	Form::operator=(const Form& other)
{
	if (this == &other)
		return (*this);
	std::cout << BOLD << BLACK << "[OVRLRD]" << RESET << " ";
	
	return (*this);
}

Form::~Form()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " shredded." << std::endl;
}

const bool&			Form::getIsSigned() const { return (isSigned); }
const int&			Form::getMinSign() const { return (minSign); }
const int&			Form::getMinExec() const { return (minExec); }
const std::string&	Form::getName() const { return (name); }

void	Form::beSigned(Bureaucrat brcrat)
{
	
}
