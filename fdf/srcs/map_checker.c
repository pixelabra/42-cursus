/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:09 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/05 23:32:55 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	file_type(char **argv)
{
	int		fd_map;
	int		height;
	int		width;
	char	*line;

	height = 0;
	width = 0;
	if (ft_strncmp(argv[1][ft_strlen(argv[1] - 4)], ".fdf", 4))
		ft_error(2, NULL);
	fd_map = open(argv[2], O_RDONLY);
	if (fd_map < 0)
		ft_error(1, argv[1]);
	line = get_next_line(fd_map);
	while (line)
	{
		width = ft_wc(line, ' ');
		if (width)
		free(line);
		line = get_next_line(fd_map);
	}
	
	
}

// void	file_formatting(char **argv)
// {
// 	int	old_width;
// 	int	new_width;

// 	old_width = 0;
// 	new_width = 0;
// }