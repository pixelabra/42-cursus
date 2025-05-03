/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 19:27:11 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include <sstream>

int	main(void)
{
	// Test: ShrubberybCreationForm (stack + heap, copy + assignment)
	{
		AForm*		shrooby;
		
		shrooby = NULL;
		try {
			Bureaucrat				appowo("appowo", 11);
			ShrubberyCreationForm	d_shrub;
			ShrubberyCreationForm	shrub2("shrub2");
			ShrubberyCreationForm	shrooby2(shrub2);
			
			shrooby2 = d_shrub;
			shrooby = new ShrubberyCreationForm("shrooby");
			appowo.signForm(*shrooby);
			appowo.executeForm(*shrooby);
			std::cout << "---------------" << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Unforeseen problem encountered.\n";
		}
		std::cout << "---------------" << std::endl;
		if (shrooby) {
			delete shrooby;
		}
	}
	std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
	// Test: RobotomyRequestForm (stack + heap, copy + assignment)
	{
		AForm*		rooby;
		
		rooby = NULL;
		try {
			Bureaucrat				appowo("appowo", 44);
			RobotomyRequestForm		d_roob;
			RobotomyRequestForm		ruby2("ruby2");
			RobotomyRequestForm		rooby2(ruby2);
			
			rooby2 = d_roob;
			rooby = new RobotomyRequestForm("rooby");
			appowo.signForm(*rooby);
			appowo.executeForm(*rooby);
			std::cout << "---------------" << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Unforeseen problem encountered.\n";
		}
		std::cout << "---------------" << std::endl;
		if (rooby) {
			delete rooby;
		}
	}
	std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
	// Test: PresidentialPardonForm (stack + heap, copy + assignment)
	{
		AForm	*prooby;
		
		prooby = NULL;
		try {
			Bureaucrat					lunesy("lunesy", 5);
			PresidentialPardonForm		d_presidente;
			PresidentialPardonForm		presidente2("presidente2");
			PresidentialPardonForm		prooby2(presidente2);
			
			prooby2 = d_presidente;
			prooby = new PresidentialPardonForm("prooby");
			lunesy.signForm(*prooby);
			lunesy.executeForm(*prooby);
			std::cout << "---------------" << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what();
			std::cout << "---------------" << std::endl;
		} catch (...) {
			std::cerr << "Unforeseen problem encountered.\n";
		}
		std::cout << "---------------" << std::endl;
		if (prooby) {
				delete prooby;
			}
		}
		// std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
		{
			int			N = 10;
			AForm		*forms[N];
			std::string	target = "target";
			Bureaucrat	appowo("appowo", 5);
			
			for (int i = 0; i < N; i++) {
				forms[i] = NULL;
			}
			for (int i = 0; i < N; i++) {
				std::ostringstream oss;
				oss << target << "[" << i << "]";
				if (i % 3 == 0) {
					forms[i] = new PresidentialPardonForm(oss.str());
				} else if (i % 3 == 1) {
					forms[i] = new RobotomyRequestForm(oss.str());
				} else if (i % 3 == 2) {
					forms[i] = new ShrubberyCreationForm(oss.str());
				}
			}
			for (int i = 0; i < N; i++) {
				try {
					appowo.signForm(*forms[i]);
				} catch (std::exception& e) {
					std::cerr << e.what();
					std::cout << "---------------" << std::endl;
				} catch (...) {
					std::cerr << "Unforeseen problem encountered.\n";
				}
			}
			for (int i = 0; i < N; i++) {
				try {
					appowo.executeForm(*forms[i]);
				} catch (std::exception& e) {
					std::cerr << e.what();
					std::cout << "---------------" << std::endl;
				} catch (...) {
					std::cerr << "Unforeseen problem encountered.\n";
			}
		}
		for (int i = 0; i < N; i++) {
			if (forms[i]) {
				delete forms[i];
			}
		}
	}
	return (0);
}
