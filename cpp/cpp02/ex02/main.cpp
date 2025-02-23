/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:41:09 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/26 23:55:24 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

#define PRINT(X) std::cout << X << std::endl

int main(void)
{
	Fixed		a;
	Fixed const	b(Fixed(5.05f) * Fixed(2));


	std::cout << Fixed::max(a, b) << std::endl;
	std::cout << Fixed::min(a, b) << std::endl;
	
	std::cout << (a < b) << std::endl;

	return (0);
}
