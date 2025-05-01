/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:58:22 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 01:53:46 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
{

}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137)
{
	std::ofstream outfile((target + "_shrubbery").c_str());
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

}

// ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
// {

// }

// const ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
// {

// }

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	
}

const std::string&	ShrubberyCreationForm::getName() const
{
	return (this->AForm::getName());
}
