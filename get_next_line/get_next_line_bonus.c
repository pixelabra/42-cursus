/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:37:30 by agodeanu          #+#    #+#             */
/*   Updated: 2023/12/10 21:16:02 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buff_ax[OPEN_MAX][BUFFER_SIZE + 1u];
	char		*line;
	int			read_var;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	while (!line || !ft_strchr(line, '\n'))
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
		line = ft_appender(buff_ax[fd], line);
	}
	return (line);
}
