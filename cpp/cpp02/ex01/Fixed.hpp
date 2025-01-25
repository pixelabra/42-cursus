/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:41:46 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/26 00:29:26 by agodeanu         ###   ########.fr       */
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
		~Fixed();
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		void	printfx_nbr(void) const;
};

std::ostream&	operator<<(std::ostream& stream, const Fixed& fixed);
#endif
