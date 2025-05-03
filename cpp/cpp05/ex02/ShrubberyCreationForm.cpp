/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:58:22 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 18:30:28 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("shrubless", 145, 137), target("trgtless")
{
	std::cout << BOLD << BLUE << "[d_CONSTR]" << RESET << " ";
	std::cout << "SHRB --> trgt: " << target << " created.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string _target):
	AForm("ShrubberyCreationForm", 145, 137), target(_target)
{
	std::cout << BOLD << MAGENTA << "[p_CONSTR]" << RESET << " ";
	std::cout << "SHRB --> trgt: " << target << " created.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other):
	AForm(other.getName(), other.getMinSign(), other.getMinExec()), target(other.target)
{
	std::cout << BOLD << YELLOW << "[c_CONSTR]" << RESET << " ";
	std::cout << "SHRB --> trgt: " << target << ", " << this->getName()  << "(" << "S-" << this->getMinSign()  << ", E-"<< this->getMinExec();
	std::cout << ")" << " copied." << std::endl;
}

const ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this == &other)
		return (*this);
	AForm::operator=(other);
	std::cout << "SHRB (trgt: " << target << ") --> (trgt: " << other.target << ").\n";
	target = other.target;
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << BOLD << RED << "[DESTR]" << RESET << " ";
	std::cout << "SHRB " << this->getName() << "(" << "S-" << this->AForm::getMinSign() << ", E-"<< this->getMinExec();
	std::cout << ")" << " shredded shrublessly." << std::endl;
}

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	AForm::execute(executor);
	std::cout << executor.getName() << "(" << executor.getGrade() << ")" 
		<< " is trying to execute SHRB " << this->getName()  << "(" << "S-"
		<< this->getMinSign() << ", E-"<< this->getMinExec() << ")" << std::endl;
	std::ofstream outfile((target + "_shrubbery").c_str());
	if (outfile.fail()) {
		std::cout << "but execution is unsuccessful.\n";
		std::cout << "---------------" << std::endl;
		throw std::runtime_error(BOLD CYAN "[EXCPT] " RESET + target + "_shrubbery: Failed to open file.\n");
	}
	outfile << "      /\\\n"
	        << "     /**\\\n"
	        << "    /****\\     /\\\n"
	        << "   /******\\   /**\\\n"
	        << "  /********\\ /****\\\n"
	        << " /**********\\******\\\n"
	        << "/***\\********\\******\\\n"
	        << "/****\\********\\*****\\\n"
	        << "       |||     xxx\n"
	        << "      /|||\\    xxx\n"
	        << "     //|||\\\\   xxx\n"
	        << "    ///|||\\\\\\\n"
	        << "    ||||||||||\n";
	outfile.close();
	std::cout << " execution successful.\n";
	std::cout << "SHRB " << BOLD << target + "_shrubbery" << RESET << "(FILE) created.\n";
}
