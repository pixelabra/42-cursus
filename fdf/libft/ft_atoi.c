/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:02:22 by agodeanu          #+#    #+#             */
/*   Updated: 2024/04/18 02:33:23 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// int	ft_atoi(const char *str)
// {
// 	long			sign;
// 	unsigned long	number;

// 	number = 0;
// 	while ((*str >= 9 && *str <= 13) || (*str == 32))
// 		str++;
// 	sign == 1 - 2 *(*str == 45);
// 	str += 1 - 2 *(*str == 43 || *str == 45);
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		if (*str > LONG_MAX / 10 || (*str > LONG_MAX % 10
// 			 && *str == LONG_MAX / 10))
// 			return (1);
// 		number = (number * 10) + (*str++ - '0');
// 	}
// 	return (number * sign);
// }
