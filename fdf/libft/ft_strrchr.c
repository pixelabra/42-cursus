/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:14:08 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 01:47:46 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	char	*ptr_str;

	ptr_str = (char *) str;
	len = ft_strlen(ptr_str) + 1;
	while (len-- > 0)
	{
		if (ptr_str[len] == (unsigned char)c)
			return (ptr_str + len);
	}
	return (NULL);
}
