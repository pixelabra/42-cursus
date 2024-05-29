/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:37:30 by agodeanu          #+#    #+#             */
/*   Updated: 2024/03/30 14:44:05 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buff_ax[1024][BUFFER_SIZE + 1u];
	char		*line;
	int			read_var;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	while (!line || !gnl_strchr(line, '\n'))
	{
		if (!(*buff_ax[fd]))
		{
			read_var = read(fd, buff_ax[fd], BUFFER_SIZE);
			if (read_var < 0)
			{
				if (line)
					free(line);
				return (NULL);
			}
			if (read_var == 0)
				return (line);
			buff_ax[fd][read_var] = '\0';
		}
		line = gnl_appender(buff_ax[fd], line);
	}
	return (line);
}
