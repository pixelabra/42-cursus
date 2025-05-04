/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 20:33:34 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

int	main(void)
{
	{
		try {
			Intern	someRandomIntern;
			AForm	*rrf;

			rrf = someRandomIntern.makeForm("shrubbery request", "Bender");
			std::cout << "---------------" << std::endl;
			if (rrf) {
				delete rrf;
			}
		} catch (std::exception& e) {
			std::cerr << e.what();
			std::cout << "---------------" << std::endl;
		} catch (...) {
			std::cerr << "Unforeseen problem encountered.\n";
		}
	}
	return (0);
}
