/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:01:55 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/01 18:57:38 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(): name("blank"), minSign(150), minExec(150), isSigned(false)
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
	if (minSign < 1 || minExec < 1) {
		std::cout << name << ": ";
		throw GradeTooHighException();
	}
	isSigned = false;
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " created." << std::endl;
}

Form::Form(const Form& other): name(other.name), minSign(other.minSign),
	minExec(other.minExec), isSigned(other.isSigned)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "form " << name << "(" << "S-" << minSign << ", E-"<< minExec;
	std::cout << ")" << " copied." << std::endl;
}

Form&	Form::operator=(const Form& other)
{
	if (this == &other) {
		return (*this);
	}
	std::cout << BOLD << BLACK << "[OVRLRD]" << RESET << " ";
	std::cout << "forms are not equal.\n";
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

void	Form::beSigned(Bureaucrat& brcrat)
{
	if (brcrat.getGrade() > minSign) {
		throw GradeTooLowException(brcrat.getName()
			+ " couldn't sign '" + name + "' because grade too low\n");
	}
	if (!isSigned) {
		std::cout << brcrat.getName() << " signed ";
		std::cout << *this;
		isSigned = true;
	} else {
		std::cout << "form '" << this->getName() << "' alreay signed.\n";
	}
}

Form::GradeTooHighException::GradeTooHighException():
	message("level higher than 1 not allowed.\n") {}

Form::GradeTooHighException::GradeTooHighException(std::string _message):
	message(_message) {}

Form::GradeTooLowException::GradeTooLowException():
	message("level lower than 150 not allowed.\n") {}

Form::GradeTooLowException::GradeTooLowException(std::string _message):
	message(_message) {}

Form::GradeTooHighException::~GradeTooHighException() throw() {}
Form::GradeTooLowException::~GradeTooLowException() throw() {}

const char *Form::GradeTooHighException::what() const throw()
{
	std::cout << "---------------" << std::endl;
	std::cout << BOLD << CYAN << "[EXCPT]" << RESET << " ";
	return (message.c_str());
}

const char *Form::GradeTooLowException::what() const throw()
{
	std::cout << "---------------" << std::endl;
	std::cout << BOLD << CYAN << "[EXCPT]" << RESET << " ";
	return (message.c_str());
}

std::ostream&	operator<<(std::ostream& stream, const Form& other)
{
	stream << "form " << other.getName() << "(" << "S-" << other.getMinSign();
	stream << ", E-"<< other.getMinExec() << ")" << std::endl;
	return (stream);
}
