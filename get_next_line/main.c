/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:44:05 by agodeanu          #+#    #+#             */
/*   Updated: 2024/01/21 19:18:46 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	int	fd[3];
	char	*line;
	int	i;

	i = 0;
	fd[0] = open("textfile.txt", O_RDONLY);
	fd[1] = open("textfile2.txt", O_RDONLY);
	fd[2] = open("textfile3.txt", O_RDONLY);
	while (i < 3)
	{
		line = get_next_line(fd[i]);
		if (!line)
			printf("Unable to read file%d\n", i++ - 1);
		else
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd[i]);
			close(fd[i++]);
		}
	}
	return (0);
}
