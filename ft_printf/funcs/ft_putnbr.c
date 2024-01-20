/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:56:20 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/25 23:56:22 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long number)
{
	int		counter;

	counter = 0;
	if (number < 0)
		return (ft_putchar('-') + ft_putnbr(-number));
	if (number < 10)
		return (ft_putchar((int)number + '0'));
	else
	{
		counter += ft_putnbr(number / 10);
		return (counter + ft_putnbr(number % 10));
	}
}
