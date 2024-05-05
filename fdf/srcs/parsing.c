/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:51:06 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/05 23:24:00 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(int error_code, char *str)
{
	if (error_code == 1)
		perror(str);
	if (error_code == 2)
	{
		ft_putendl_fd("Map file should end in fdf.", 2);
		exit(0);
	}
}

int	get_height(char **argv)
{
	int		fd_map;
	int		height;
	char	*line;

	height = 0;
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, argv[1]);
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

//What happens when the length is 0? Like \n\n\n\n\n for example
int	get_width(char **argv)
{
	char	*line;
	int		fd_map;
	int		length;

	length = 0;
	fd_map = open(argv[1], O_RDONLY);
	line = get_next_line(fd_map);
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

	i = 0;
	points = ft_split(line, ' ');
	while (points[i])
	{
		if (ft_strncmp(points[i], "\n", 1))
		{
			row[i].x = i;
			row[i].y = current_line;
			row[i].z = ft_atoi(points[i]);
			row[i].colour = 0xFFFFFF;
		}
		free(points[i]);
		i++;
	}
	if (points)
		free(points);
}

	void	build_matrix(t_mlx_data *data, char **argv)
{
	int	i;
	int fd_map;
	char *line;

	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, argv[1]);
	data->height = get_height(argv);
	data->width = get_width(argv);
	data->matrix = malloc(sizeof(t_coord *) * data->height + 1);
	i = 0;
	while (i < data->height)
		data->matrix[i++] = malloc(sizeof(t_coord) * data->width);
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
