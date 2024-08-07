/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:14:15 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/07 19:56:39 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr(set, (int)s1[i]))
		i++;
	len = ft_strlen(s1);
	if (i == len)
		return (ft_strdup(""));
	while ((i < len - 1) && ft_strchr(set, (int)s1[len - 1]))
		len--;
	trim_str = malloc(sizeof(char) * (len - i + 1 + (i != ft_strlen(s1))));
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, s1 + i, len - i + 1 + (i != ft_strlen(s1)));
	return (trim_str);
}
