/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:25:12 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:25:12 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wc(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (str && *str)
	{
		if (*str != c)
		{
			while (*str && *str != c)
				str++;
			count++;
		}
		if (!(*str))
			break ;
		str++;
	}
	return (count);
}
