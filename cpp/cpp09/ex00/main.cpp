/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:14:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/09/14 15:39:44 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main() {

	BitcoinExchange	bitcoin("2022-12-12", 50000.0);

	std::cout << bitcoin.isValidValue("5000.0f") << std::endl;
	return (0);
}
