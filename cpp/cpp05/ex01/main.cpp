/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 20:55:36 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

int	main(void)
{
	{
		Form		fwom;
		Form		*fwomseytunesy;
		Form		formwoof(fwom);

		fwomseytunesy = NULL;
		try {
			Form	fwomsify("fwomsify", 85, 24);
			fwomseytunesy = new Form("fwomseytunesy", 13, 28);
			fwom = *fwomseytunesy;
			std::cout << "---------------" << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Encountered an unforeseen problem.\n";
		}
		std::cout << "---------------" << std::endl;
		if (fwomseytunesy) {
			delete fwomseytunesy;
		}
	}
	std::cout << BOLD << WHITE << ">INTERMEZZO<\n" << RESET;
	{
		try {
			Bureaucrat	lunesy("lunesy", 26);
			Form		f1("appowoTermination", 24, 12);

			lunesy.promote();
			lunesy.promote();
			lunesy.signForm(f1);
			// lunesy.demote();
			lunesy.signForm(f1);
			std::cout << "---------------" << std::endl;
		} catch (std::exception& e) {
			std::cerr << e.what();
		} catch (...) {
			std::cerr << "Encountered an unforeseen problem.\n";
		}
	}
	return (0);
}
