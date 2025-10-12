/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:32 by agodeanu          #+#    #+#             */
/*   Updated: 2025/10/12 21:16:43 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av) {
	if (ac < 2 || !validateArguments(av)) {
		std::cerr << "NOT GOOD" << std::endl;
		return 1;
	}
	try {
		PmergeMe mergeMe(av);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unforeseen problem " << std::endl;
	}
	return 0;
}
