/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:09 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/07 00:59:00 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_file_ext(char *file_name)
{
	if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".fdf", 4))
		ft_error(2, NULL);
}

int	read_first_line(int fd_map, char **line)
{
	int	width;

	width = 0;
	*line = get_next_line(fd_map);
	if (!(*line))
		ft_error(2, NULL);
	if ((*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = ' ';
	width = ft_wc(*line, ' ');
	if (!width)
		ft_error(3, *line);
	return (width);
}

void	check_map_formatting(int fd_map, int exp_width, char **argv)
{
	char	*line;
	int		current_width;
	int		height;

	height = get_height(argv) - 1;
	while (height--)
	{
		line = get_next_line(fd_map);
		if (!line)
		{
			close(fd_map);
			ft_error(2, NULL);
		}
		if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = ' ';
		current_width = ft_wc(line, ' ');
		if (current_width != exp_width)
		{
			ft_error(3, line);
			close(fd_map);
		}
		free(line);
	}
}

void	file_checker(char **argv)
{
	int		fd_map;
	int		width;
	char	*line;

	check_file_ext(argv[1]);
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, NULL);
	width = read_first_line(fd_map, &line);
	free(line);
	check_map_formatting(fd_map, width, argv);
	close(fd_map);
}
