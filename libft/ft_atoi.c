/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:02:22 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/06 16:55:26 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long		sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((result == 922337203685477580
				&& str[i] > '7') || (result > 922337203685477580))
			return (-1 * (sign != -1));
		result = (result * 10) + (str[i++] - '0');
	}
	return ((int)(result * sign));
}
