/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:50:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/02/23 17:55:08 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::bits = 8;

Fixed::Fixed(): fx_nbr(0)
{
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int nbr)
{
	std::cout << "Int constructor called\n";
	fx_nbr = nbr << bits;
}

Fixed::Fixed(const float nbr)
{
	std::cout << "Float constructor called\n";
	fx_nbr = (int)roundf((nbr * (float)(1 << bits)));
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

float	Fixed::toFloat(void) const
{
	return (float(fx_nbr) / float(1 << bits));
}

int		Fixed::toInt(void) const
{
	return (int(fx_nbr) / int(1 << bits));
}

std::ostream&	operator<<(std::ostream& stream, const Fixed& fixed)
{
	std::cout << fixed.toFloat();
	return (stream);
}

bool	Fixed::operator<(const Fixed& other)
{
	return (fx_nbr < other.fx_nbr);
}

bool	Fixed::operator>(const Fixed& other)
{
	return (fx_nbr > other.fx_nbr);
}

bool	Fixed::operator<=(const Fixed& other)
{
	return (fx_nbr <= other.fx_nbr);
}

bool	Fixed::operator>=(const Fixed& other)
{
	return (fx_nbr >= other.fx_nbr);
}

bool	Fixed::operator==(const Fixed& other)
{
	return (fx_nbr == other.fx_nbr);
}

bool	Fixed::operator!=(const Fixed& other)
{
	return (fx_nbr != other.fx_nbr);
}

Fixed	Fixed::operator+(const Fixed& other)
{
	Fixed	temp(this->toFloat() + other.toFloat());
	return (temp);
}

Fixed	Fixed::operator-(const Fixed& other)
{
	Fixed	temp(this->toFloat() - other.toFloat());
	return (temp);
}

Fixed	Fixed::operator*(const Fixed& other)
{
	Fixed	temp(this->toFloat() * other.toFloat());
	return (temp);
}

Fixed	Fixed::operator/(const Fixed& other)
{
	Fixed	temp(this->toFloat() / other.toFloat());
	return (temp);
}

Fixed&	Fixed::operator++(void)
{
	++this->fx_nbr;
	return (*this);
}

Fixed&	Fixed::operator--(void)
{
	--this->fx_nbr;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	temp(*this);

	++this->fx_nbr;
	return (temp);
}

Fixed	Fixed::operator--(int)
{
	Fixed	temp(*this);

	--this->fx_nbr;
	return (temp);
}

Fixed&	Fixed::min(Fixed& f1, Fixed& f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed&	Fixed::max(Fixed& f1, Fixed& f2)
{
	if (f1 < f2)
		return (f2);
	return (f1);
}

const Fixed&	Fixed::min(const Fixed& f1, const Fixed& f2)
{
	if (f1.toInt() < f2.toInt())
		return (f1);
	return (f2);
}

const Fixed&	Fixed::max(const Fixed& f1, const Fixed& f2)
{
	if (f1.toInt() > f2.toInt())
		return (f1);
	return (f2);
}
