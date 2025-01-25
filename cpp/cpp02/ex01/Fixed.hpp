/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:41:46 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/22 00:49:48 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int					fx_nbr;
		static const int	bits;
	public:
		Fixed();
		Fixed(const Fixed& other);
		Fixed::Fixed(const int nbr);
		Fixed::Fixed(const float nbr);
		Fixed&	operator=(const Fixed& other);
		~Fixed();
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
};

#endif