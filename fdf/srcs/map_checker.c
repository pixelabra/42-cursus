/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:09 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/10/30 02:00:38 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(int error_code, char *line, int fd_map)
{
	if (error_code == 1)
		ft_putendl_fd("Map file should end in '.fdf'.", 2);
	else if (error_code == 2)
		ft_putendl_fd("Unable to read/open the file.", 2);
	else if (error_code == 3)
		ft_putendl_fd("File Empty or no non-space characters", 2);
	else if (error_code == 4)
		ft_putendl_fd("Inconsistent map", 2);
	else if (error_code == 5)
		ft_putendl_fd("Argument number must be 2. Do better.", 2);
	if (line)
		free(line);
	if (fd_map > 2)
		close(fd_map);
	exit(0);
}

void	check_file_ext(char *file_name)
{
	if (ft_strncmp(file_name + ft_strlen(file_name) - 4, ".fdf", 4))
		ft_error(1, NULL, -1);
}

int	read_first_line(int fd_map, char **line)
{
	int	width;

	width = 0;
	*line = get_next_line(fd_map);
	if (!(*line))
		ft_error(2, NULL, fd_map);
	if ((*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = ' ';
	width = ft_wc(*line, ' ');
	if (!width)
		ft_error(3, *line, fd_map);
	return (width);
}

void	check_map_formatting(int fd_map, int exp_width, char **argv)
{
	char	*line;
	int		current_width;
	int		height;

	height = get_height(argv) - 1;
	while (height-- > 0)
	{
		line = get_next_line(fd_map);
		if (!line || !(*line))
			ft_error(2, NULL, fd_map);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		current_width = (int) ft_wc(line, ' ');
		if (!(exp_width) || current_width != exp_width)
			ft_error(4, line, fd_map);
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
		ft_error(2, NULL, -1);
	width = read_first_line(fd_map, &line);
	free(line);
	check_map_formatting(fd_map, width, argv);
	close(fd_map);
}
