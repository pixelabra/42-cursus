/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:59:54 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 18:30:47 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("robotomiless", 72, 45), target("trgtless")
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << "RBTM robotomiless created.\n";
}

RobotomyRequestForm::RobotomyRequestForm(std::string _target): AForm("RobotomyRequestForm", 72, 45), target(_target)
{
	std::cout << BOLD << MAGENTA << "[p_CONSTR]" << RESET << " ";
	std::cout << "RBTM --> trgt: " << target << " created.\n";
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other):
	AForm(other.AForm::getName(), other.AForm::getMinSign(), other.AForm::getMinExec()), target(other.target)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "RBTM " << this->AForm::getName()  << "(" << "S-" << this->AForm::getMinSign()  << ", E-"<< this->AForm::getMinExec();
	std::cout << ")" << " copied." << std::endl;
}

const RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	if (this == &other)
		return (*this);
	AForm::operator=(other);
	std::cout << "RBTM (trgt: " << target << ") --> (trgt: " << other.target << ").\n";
	target = other.target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << "RBTM " << this->getName() << "(" << "S-" << this->AForm::getMinSign() << ", E-"<< this->getMinExec();
	std::cout << ")" << " shredded wobotically." << std::endl;
}

void	RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);
	std::cout << executor.getName() << "(" << executor.getGrade() << ")" 
		<< " executed RBTM " << this->getName()  << "(" << "S-"
		<< this->getMinSign() << ", E-"<< this->getMinExec() << ")" << std::endl;
	std::cout << "*drill* *drill* *drill*\n";
	srand(time(0));
	if (rand() % 2 == 0) {
		std::cout << target << "'s robotomy successful.\n";
	} else {
		std::cout << target << "'s robotomy failed.\n";
	}
}
