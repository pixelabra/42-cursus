/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:51:06 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/18 02:33:12 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(int error_code, char *str)
{
	if (error_code == 1)
		perror(str);
}

int	get_width(char **argv)
{
	int		fd_map;
	int		width;
	char	*line;

	width = 0;
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, argv[1]);
	line = get_next_line(fd_map);
	while (line)
	{
		width++;
		free(line);
		line = get_next_line(fd_map);
	}
	if (!width)
		free(line);
	close(fd_map);
	return (width);
}

int	get_length(char **argv)
{
	char	*line;
	int		fd_map;
	int		length;

	length = 0;
	fd_map = open(argv[1], O_RDONLY);
	line = get_next_line(fd_map);
	length = (int) ft_wc(line, ' ');
	free(line);
	close(fd_map);
	return (length);
}

void	pop_matrix(int *row, char *line)
{
	int		i;
	char	**points;

	i = 0;
	points = ft_split(line, ' ');
	while (points[i])
	{
		row[i] = atoi(points[i]);
		free(points[i]);
		i++;
	}
	free(points);
}

void	build_matrix(mlx_data *mx_var, char **argv)
{
	int	i;
	int fd_map;
	char *line;

	i = 0;
	fd_map = open(argv[1], O_RDONLY);
	mx_var->length = get_length(argv);
	mx_var->width = get_width(argv);
	mx_var->matrix = malloc(sizeof(int *) * (mx_var->width + 1));
	while (i < mx_var->width)
		mx_var->matrix[i++] = malloc(sizeof(int) * mx_var->length + 1);
	line = get_next_line(fd_map);
	while (line)
	{
		pop_matrix(mx_var->matrix[i++], line);
		free(line);
		line = get_next_line(fd_map);
	}
	if (!line)
		free(line);
	mx_var->matrix[i] = NULL;
}