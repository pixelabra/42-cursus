/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:14:15 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 00:05:51 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	char	*ptr_s1;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (s1[i] && ft_strchr(set, (int) s1[i]) != NULL)
		i++;
	while (len - 1 > i && ft_strchr(set, (int)s1[len - 1]) != NULL)
		len--;
	trim_str = malloc(sizeof(char) * (len - i + 1 + (i != ft_strlen(s1))));
	if (!trim_str)
		return (NULL);
	ptr_s1 = (char *) s1 + i;
	ft_strlcpy(trim_str, ptr_s1, len - i + 1 + (i != ft_strlen(s1)));
	return (trim_str);
}
