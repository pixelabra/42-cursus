/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:56:11 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/25 23:56:13 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long number, int base, int check)
{
	int		counter;
	char	*base_char;

	counter = 0;
	if (check)
		base_char = "0123456789ABCDEF";
	else
		base_char = "0123456789abcdef";
	if (number < (unsigned long) base)
		return (ft_putchar(base_char[number]));
	else
	{
		counter = ft_putnbr_base(number / base, base, check);
		return (counter + ft_putnbr_base(number % base, base, check));
	}
}
