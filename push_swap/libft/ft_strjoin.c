/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:11:54 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 00:03:48 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str_join = (char *) malloc(sizeof(char) * (len + 1));
	if (!str_join)
		return (NULL);
	*str_join = '\0';
	ft_strlcat(str_join, s1, len + 1);
	ft_strlcat(str_join, s2, len + 1);
	return (str_join);
}
