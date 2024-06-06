/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:51:06 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/07 02:59:00 by a3y3g1           ###   ########.fr       */
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

void	pop_matrix(t_coord *row, char *line, int current_line)
{
	int		i;
	char	**points;
	char	**coord;

	i = 0;
	points = ft_split(line, ' ');
	while (points[i])
	{
		if (ft_strncmp(points[i], "\n", 1))
		{
			coord = ft_split(points[i], ',');
			row[i].x = i;
			row[i].y = current_line;
			row[i].z = ft_atoi(coord[0]);
			if (coord[1])
				row[i].colour = ft_htoi(coord[1]);
			else
				row[i].colour = 0xFFFFFFFF;
			free(coord[0]);
			if (coord[1])
				free(coord[1]);
			free(coord);
		}
		free(points[i]);
		i++;
	}
	free(points);
}

void	alloc_matrix(t_mlx_data *data, char **argv, int fd_map)
{
	int	i;

	data->height = get_height(argv);
	data->width = get_width(argv);
	data->matrix = malloc(sizeof(t_coord *) * data->height);
	if (!data->matrix)
	{
		close(fd_map);
		free_init(data);
	}
	i = 0;
	while (i < data->height)
	{
		data->matrix[i] = malloc(sizeof(t_coord) * data->width);
		if (!data->matrix[i])
		{
			close(fd_map);
			free_init(data);
		}
		i++;
	}
}

void	build_matrix(t_mlx_data *data, char **argv)
{
	int	i;
	int fd_map;
	char *line;

	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, NULL, -1);
	alloc_matrix(data, argv, fd_map);
	i = 0;
	line = get_next_line(fd_map);
	while (line)
	{
		pop_matrix(data->matrix[i], line, i + 1);
		free(line);
		line = get_next_line(fd_map);
		i++;
	}
	close(fd_map);
}
