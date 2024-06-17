/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:23:55 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:23:58 by agodeanu         ###   ########.fr       */
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
