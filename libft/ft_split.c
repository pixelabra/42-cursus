/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:11:13 by agodeanu          #+#    #+#             */
/*   Updated: 2023/11/16 00:02:49 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			i++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	return (i);
}

static char	*ft_strdup2(const char *src, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] != c && src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**s_split;
	int		i;
	int		j;
	int		words;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = ft_size((char *)s, c);
	s_split = (char **) malloc(sizeof(char *) * (words + 1));
	if (!s_split)
		return (NULL);
	while (s[i] && j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		s_split[j++] = ft_strdup2(s + i, c);
		i += ft_strlen(s_split[j - 1]) + 1;
	}
	s_split[j] = NULL;
	return (s_split);
}
