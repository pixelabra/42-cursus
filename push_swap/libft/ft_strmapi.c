/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:13:19 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/15 23:13:26 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr_s;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	ptr_s = (char *) malloc(sizeof(char) * (ft_strlen((char *) s) + 1));
	if (!ptr_s)
		return (NULL);
	while (s[i])
	{
		ptr_s[i] = f(i, s[i]);
		i++;
	}
	ptr_s[i] = '\0';
	return (ptr_s);
}
