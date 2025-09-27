/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:14:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/09/14 15:57:55 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char **av) {
	try {
		BitcoinExchange	btc(av[1]);

		btc.evaluateInput();
	} catch (std::exception& e) {
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Unforeseen problem encountered" << std::endl;
	}
	(void)ac;
	return (0);
}
