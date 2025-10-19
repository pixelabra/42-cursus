/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:32 by agodeanu          #+#    #+#             */
/*   Updated: 2025/10/19 23:26:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av) {
	if (ac < 2 || !validateArguments(av)) {
		std::cerr << "Provide positive integers as arguments " << std::endl;
		return 1;
	}
	try {
		PmergeMe mergeMe(av);
		std::vector<int> vectie = mergeMe.getVect();
		std::list<int> listie = mergeMe.getList();

		std::cout << "VECTOR: ";
		printContainer(vectie);
		std::cout << std::endl;
		std::cout << "LIST: ";
		printContainer(listie);
		std::cout << "VECTOR SORTED: " << isSorted(vectie) << std::endl;
		std::cout << "LIST SORTED: " << isSorted(listie) << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem " << std::endl;
	}
	return 0;
}
