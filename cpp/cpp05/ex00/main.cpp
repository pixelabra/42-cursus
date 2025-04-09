/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/10 01:42:15 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat	*lunesyHorde[10];

	try {
		// Bureaucrat	apowo;
		// Bureaucrat	lunesy("lunesy", 12);
		// Bureaucrat	*lunesytoonesy = new Bureaucrat("lunesytoonesy", 155);

		for (int i = 0; i < 10; i++)
			lunesyHorde[i] = new Bureaucrat("lunesypaloonesy", 147 + i);
		for (int i = 0; i < 10; i++)
			std::cout << lunesyHorde[i] << std::endl;
		// std::cout << apowo << std::endl;
		// std::cout << *lunesytoonesy << std::endl;
		for (int i = 0; i < 10; i++)
			delete lunesyHorde[i];
		}
		catch(Bureaucrat::GradeTooHighException& e) {
			std::cout << e.what();
		}
		catch(Bureaucrat::GradeTooLowException& e) {
			std::cout << e.what();
	} 
	catch(...) {
		std::cout << "Encountered an unforeseen problem\n";
	}
	for (int i = 0; i < 10; i++)
		delete lunesyHorde[i];
	return (0);
}
