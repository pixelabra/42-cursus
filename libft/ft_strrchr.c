/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:14:08 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/07 20:15:54 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	slen;

	if (!str)
		return (NULL);
	slen = ft_strlen(str);
	if (!(unsigned char)c)
		return ((char *)&str[slen]);
	while (slen >= 0)
	{
		if (str[slen] == (unsigned char)c)
			return ((char *)&str[slen]);
		slen--;
	}
	return (NULL);
}
