/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:30:49 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 17:52:33 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << "INTRN created. No one cares.\n";
}

Intern::Intern(const Intern& other)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "INTRN copied. Nothing happened.\n";\
	(void)other;
}

Intern&	Intern::operator=(const Intern& other)
{
	if (this == &other) {
		return (*this);
	}
	std::cout << "INTRNs are equal already. nothing = nothing.\n";
	return (*this);
}

Intern::~Intern()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << "INTRN is gone. Oh noo...\n";
}

AForm	*Intern::makeForm(std::string formName, std::string targetForm) const
{
	int		i;
	AForm	*result;
	std::string	forms[3] = {"robotomy request", "presidential request", "shrubbery request"};

	for (i = 0; i < 3; i++) {
		if (formName == forms[i]) {
			break ;
		}
	}
	switch (i)
	{
		case 0:
			result = new RobotomyRequestForm(targetForm);
			break ;
		case 1:
			result = new PresidentialPardonForm(targetForm);
			break ;
		case 2:
			result = new ShrubberyCreationForm(targetForm);
			break ;
		default:
			throw FormCreationFailedException("Intern was not able to create the form. incompetence!\n");
	}
	return (result);
}

Intern::FormCreationFailedException::FormCreationFailedException(std::string _message):
	message(_message) {}

Intern::FormCreationFailedException::~FormCreationFailedException() throw() {}

const char *Intern::FormCreationFailedException::what() const throw()
{
	std::cout << "---------------" << std::endl;
	std::cout << BOLD << CYAN << "[EXCPT]" << RESET << " ";
	return (message.c_str());
}
