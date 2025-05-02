/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:57:05 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 18:30:39 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): AForm("pardonless", 25, 5), target("trgtless")
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << "PRDN pardonless created.\n";
}

PresidentialPardonForm::PresidentialPardonForm(std::string _target):
	AForm("PresidentialPardonForm", 25, 5), target(_target)
{
	std::cout << BOLD << MAGENTA << "[p_CONSTR]" << RESET << " ";
	std::cout << "PRDN --> trgt: " << target << " created.\n";
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other):
AForm(other.AForm::getName(), other.AForm::getMinSign(), other.AForm::getMinExec())
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "PRDN " << this->AForm::getName()  << "(" << "S-" << this->AForm::getMinSign()  << ", E-"<< this->AForm::getMinExec();
	std::cout << ")" << " copied." << std::endl;
}

const PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	if (this == &other)
	return (*this);
	AForm::operator=(other);
	std::cout << "PRDN (trgt: " << target << ") --> (trgt: " << other.target << ").\n";
	target = other.target;
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << "PRDN " << this->getName() << "(" << "S-" << this->AForm::getMinSign() << ", E-"<< this->getMinExec();
	std::cout << ")" << " shredded presidentially." << std::endl;
}

void	PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);
	std::cout << executor.getName() << "(" << executor.getGrade() << ")" 
		<< " executed PRDN " << this->getName()  << "(" << "S-"
		<< this->getMinSign() << ", E-"<< this->getMinExec() << ")" << std::endl;
	std::cout << "PRDN " << target << " has been pardoned by Zaphod Beeblebrox.\n";
}
