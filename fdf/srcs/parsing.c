/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:51:06 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/17 02:28:49 by a3y3g1           ###   ########.fr       */
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
	char	**row;

	row = ft_split(	);	
}
