/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:41:46 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/26 20:34:43 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
	private:
		int					fx_nbr;
		static const int	bits;
	public:
		Fixed();
		Fixed(const Fixed& other);
		Fixed(const int nbr);
		Fixed(const float nbr);
		Fixed&	operator=(const Fixed& other);
		bool	operator<(const Fixed& other);
		bool	operator>(const Fixed& other);
		bool	operator<=(const Fixed& other);
		bool	operator>=(const Fixed& other);
		bool	operator==(const Fixed& other);
		bool	operator!=(const Fixed& other);
		Fixed	operator+(const Fixed& other);
		Fixed	operator-(const Fixed& other);
		Fixed	operator*(const Fixed& other);
		Fixed	operator/(const Fixed& other);
		Fixed&	operator++(void);
		Fixed&	operator--(void);
		Fixed	operator++(int);
		Fixed	operator--(int);
		~Fixed();
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		static Fixed&	min(Fixed& fx_one, Fixed& fx_two);
		static Fixed&	max(Fixed& fx_one, Fixed& fx_two);
		static const Fixed&	min(const Fixed& fx_one, const Fixed& fx_two);
		static const Fixed&	max(const Fixed& fx_one, const Fixed& fx_two);
};

std::ostream&	operator<<(std::ostream& stream, const Fixed& fixed);
#endif
