/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:55:46 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/26 00:06:35 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funcs/ft_printf.h"

static int	ft_printflag(char flag, va_list args)
{
	if (flag == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (flag == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (flag == 'd' || flag == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (flag == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), 10, 0));
	else if (flag == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), 16, 0));
	else if (flag == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), 16, 1));
	else if (flag == 'p')
		return (ft_putmem(va_arg(args, void *)));
	else if (flag == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			i = ft_printflag(*(++str), args);
			if (i == -1)
				return (-1);
			count += i;
		}
		else
			count += ft_putchar((int)*str);
		str++;
	}
	va_end(args);
	return (count);
}
