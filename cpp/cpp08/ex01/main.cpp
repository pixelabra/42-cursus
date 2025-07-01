/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:35:41 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/01 19:08:30 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main(void) {
	srand(time(0));
	Span			a(73);
	const size_t	nFill = 18;
	const size_t	nDiv = 1000;

	try {
		a.fillSpan(nFill, nDiv);
		a.longestSpan();
		a.shortestSpan();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}
	std::cout << BLUE BOLD << "INTERLUDE" << RESET << std::endl;
	try {
		// std::vector<int>		cont;
		// fillIt(cont, nFill, nDiv);

		// std::list<int>		cont;
		// fillIt(cont, nFill, nDiv);
	
		std::deque<int>		cont;
		fillIt(cont, nFill, nDiv);

		for (int i = 0; i < 2; i++) {
			a.fillSpanRange(cont.begin(), cont.end());
		}
		a.printVector();
		a.longestSpan();
		a.shortestSpan();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}
	return (0);
}
