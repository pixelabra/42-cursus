/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:24:58 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/01 18:35:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <cstdlib>

int	main() {
	int	N = 10;
	
	srand(time(0));
	std::cout << BOLD MAGENTA "INTEGER STUFFSIES" RESET << std::endl;
	try {
		Array<int>			intArr(N);

		for (size_t i = 0; i < intArr.size(); i++) {
			intArr[i] = rand() % 50;
		}
		intArr.printElements();
		std::cout << BOLD YELLOW << "Copy Array: " << RESET << std:: endl;
		Array<int>			intArrCopy(intArr);
		intArrCopy.printElements();
		intArr[15] = 42;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}

	std::cout << std::endl << BOLD BLUE "STRING STUFFSIES" RESET << std::endl;
	try {
		Array<std::string>	defaultStr;
		Array<std::string>	strArrLeft(N);

		for (size_t j = 0; j < strArrLeft.size(); j++) {
			for (size_t i = 0; i < 10; i++) {
				strArrLeft[j] += rand() % 26 + 'a';
			}
		}
		strArrLeft.printElements();
		Array<std::string>	strArrRight(2 * N);
		for (size_t j = 0; j < strArrRight.size(); j++) {
			for (size_t i = 0; i < 10; i++) {
				strArrRight[j] += rand() % 26 + 'a';
			}
		}
		strArrLeft = strArrRight;
		std::cout << BOLD YELLOW"Same-same array: " << RESET << std::endl;
		strArrLeft.printElements();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}
	return (0);
}
