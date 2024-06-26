/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:43:50 by agodeanu          #+#    #+#             */
/*   Updated: 2024/03/30 14:48:18 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str, int nbr)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (!nbr)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != '\n')
			i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (!(unsigned char)c)
		return ((char *)&str[gnl_strlen(str, 0)]);
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str_join;
	size_t	len;
	int		i;

	i = 0;
	len = gnl_strlen(s1, 0) + gnl_strlen(s2, 1);
	str_join = malloc(sizeof(char) * (len + 1));
	if (!str_join)
		return (NULL);
	if (s1)
		gnl_memmove(str_join, s1, gnl_strlen(s1, 0));
	while (s2[i] && s2[i] != '\n')
	{
		str_join[i + gnl_strlen(s1, 0)] = s2[i];
		i++;
	}
	if (s2[i] == '\n')
		str_join[len - 1] = '\n';
	str_join[len] = '\0';
	return (str_join);
}

void	*gnl_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if (!dest && !src)
		return (NULL);
	ptr_dest = (unsigned char *) dest;
	ptr_src = (unsigned char *) src;
	if (dest > src)
	{
		while (n--)
			*(ptr_dest + n) = *(ptr_src + n);
	}
	else if (src > dest)
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	return (dest);
}

char	*gnl_appender(char *buff_ax, char *line)
{
	char	*temp;

	temp = line;
	line = gnl_strjoin(line, buff_ax);
	if (temp)
		free(temp);
	if (gnl_strchr(buff_ax, '\n'))
		gnl_memmove(buff_ax, gnl_strchr(buff_ax, '\n') + 1,
			gnl_strlen(gnl_strchr(buff_ax, '\n') + 1, 0) + 1);
	else
		buff_ax[0] = '\0';
	return (line);
}
