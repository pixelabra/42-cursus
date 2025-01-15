/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:50:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/16 01:28:54 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(): fx_nbr(0)
{
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const Fixed& other): fx_nbr(other.fx_nbr)
{
	std::cout << "Copy constructor called\n";
}

Fixed&	Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called\n";
	if (this == &other)
		return (*this);
	fx_nbr = other.fx_nbr;
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called\n";
}

int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called\n";
	return (fx_nbr);
}

void	Fixed::setRawBits(int const raw)
{
	fx_nbr = raw;
}
