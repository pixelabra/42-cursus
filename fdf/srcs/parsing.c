/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:51:06 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:34:27 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pop_colour(t_coord *row, char *points, int i)
{
	int		j;

	j = 0;
	while (points[j])
	{
		if (points[j] == ',')
		{
			row[i].z = ft_atoi(points);
			row[i].colour = ft_htoi(points + j + 1);
			return ;
		}
		j++;
	}
	row[i].z = ft_atoi(points);
	row[i].colour = 0xFFFFFFFF;
}

int	pop_matrix(t_coord *row, char *line, int current_line, int i)
{
	char	**points;

	points = ft_split(line, ' ');
	if (!points)
		return (1);
	while (points[i])
	{
		if (ft_strncmp(points[i], "\n", 1))
		{
			row[i].x = i;
			row[i].y = current_line;
			pop_colour(row, points[i], i);
			i++;
		}
	}
	free_array(points);
	return (0);
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
	int		i;
	int		fd_map;
	char	*line;

	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, NULL, -1);
	alloc_matrix(data, argv, fd_map);
	i = 0;
	line = get_next_line(fd_map);
	while (line)
	{
		if (pop_matrix(data->matrix[i], line, i + 1, 0))
		{
			free(line);
			free_init(data);
		}
		free(line);
		line = get_next_line(fd_map);
		i++;
	}
	close(fd_map);
}
