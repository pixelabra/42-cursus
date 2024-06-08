/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:10 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 18:09:26 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_height(char **argv)
{
	int		fd_map;
	int		height;
	char	*line;

	height = 0;
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(2, NULL, -1);
	line = get_next_line(fd_map);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return (height);
}

int	get_width(char **argv)
{
	char	*line;
	int		fd_map;
	int		length;

	length = 0;
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, NULL, -1);
	line = get_next_line(fd_map);
	if (!line || !(*line))
		ft_error(2, line, fd_map);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = ' ';
	length = (int) ft_wc(line, ' ');
	free(line);
	close(fd_map);
	return (length);
}
