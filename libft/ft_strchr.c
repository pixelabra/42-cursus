/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:11:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/07 19:44:35 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (!(unsigned char)c)
		return ((char *)&s[slen]);
	slen = 0;
	while (s[slen])
	{
		if (s[slen] == (unsigned char)c)
			return ((char *)&s[slen]);
		slen++;
	}
	return (NULL);	
}
