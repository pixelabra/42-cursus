/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:52:01 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/08 13:21:56 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int	main() {
	srand(time(0));
	std::deque<int>	a;
	fillIt(a, 12);
	const std::deque<int>	b = a;
	printContainer(a);
	std::cout << GREEN BOLD << "TAU" << RESET << std::endl;
	printContainer(b);
	try {
		std::cout << BOLD CYAN << "PRE_FIND SUSPENSE" << RESET << std::endl;
		easyfind(a, 2);
		easyfind(b, 2);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen broblem." << std::endl;
	}
	return (0);
}
