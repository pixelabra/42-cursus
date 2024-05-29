/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:13:51 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 01:37:27 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_str, const char *small_str, size_t len)
{
	size_t	i;

	i = 0;
	if (!*small_str)
		return ((char *)big_str);
	while (i < len && big_str[i])
	{
		if (!ft_strncmp((char *)(big_str + i), small_str, ft_strlen(small_str))
			&& i + ft_strlen(small_str) <= len)
			return ((char *)(big_str + i));
		i++;
	}
	return (NULL);
}
