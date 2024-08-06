/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:11:13 by agodeanu          #+#    #+#             */
/*   Updated: 2024/08/06 18:12:56 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			count++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	return (count);
}

static char	*getword(const char *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

char	*freearray(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		wordcnt;
	size_t	i;
	size_t	j;

	if (!s || !c)
		return (NULL);
	wordcnt = wordcount(s, c);
	split = malloc(sizeof(char *) * (wordcnt + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < wordcnt)
	{
		while (s[i] == c)
			i++;
		split[j] = getword(&s[i], c);
		if (!split[j])
			return (freearray(split));
		i += ft_strlen(split[j++]);
	}
	split[j] = NULL;
	return (split);
}
