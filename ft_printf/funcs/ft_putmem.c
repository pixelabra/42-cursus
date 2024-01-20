/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:56:02 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/25 23:56:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putmem(void *mem)
{
	unsigned long	temp;
	int				counter;

	counter = 0;
	temp = (unsigned long) mem;
	counter += write(1, "0x", 2);
	return (counter + ft_putnbr_base(temp, 16, 0));
}
