/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:11:32 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 00:03:26 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = -1;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
