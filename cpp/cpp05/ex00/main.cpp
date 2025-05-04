/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 20:52:56 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	{
		Bureaucrat	apowo;
		Bureaucrat	*lunesytoonesy;
		Bureaucrat	apowoof(apowo);

		lunesytoonesy = NULL;
		try {
			Bureaucrat	lunesy("lunesy", 12);
			lunesytoonesy = new Bureaucrat("lunesytoonesy", 14);
			apowo = *lunesytoonesy;
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Encountered an unforeseen problem.\n";
		}
		std::cout << "---------------" << std::endl;
		if (lunesytoonesy) {
			delete lunesytoonesy;
		}
	}
	std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
	{
		Bureaucrat	*lunesyHorde[10];
		
		for (int i = 0; i < 10; i++) {
			lunesyHorde[i] = NULL;
		}
		try {
			for (int i = 0; i < 10; i++) {
				lunesyHorde[i] = new Bureaucrat("lunesypaloonesy", 147 + i);
			}
			for (int i = 0; i < 10; i++) {
				std::cout << *lunesyHorde[i] << std::endl;
			}
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Encountered an unforeseen problem.\n";
		}
		std::cout << "---------------" << std::endl;
		for (int i = 0; i < 10; i++) {
			if (lunesyHorde[i]) {
				delete lunesyHorde[i];
			}
		}
	}
	std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
	{
		Bureaucrat	luneychan("luneychan", 148);

		try {
			for (int i = 0; i < 10; i++) {
				luneychan.demote();
			}
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Encountered an unforeseen problem.\n";
		}
	}
	return (0);
}
