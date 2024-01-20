/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:37:30 by agodeanu          #+#    #+#             */
/*   Updated: 2023/12/10 20:51:11 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff_ax[BUFFER_SIZE + 1u];
	char		*line;
	int			read_var;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	while (!line || !ft_strchr(line, '\n'))
	{
		if (!(*buff_ax))
		{
			read_var = read(fd, buff_ax, BUFFER_SIZE);
			if (read_var < 0)
			{
				if (line)
					free(line);
				return (NULL);
			}
			if (read_var == 0)
				return (line);
			buff_ax[read_var] = '\0';
		}
		line = ft_appender(buff_ax, line);
	}
	return (line);
}
