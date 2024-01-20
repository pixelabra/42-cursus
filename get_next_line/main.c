/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:44:05 by agodeanu          #+#    #+#             */
/*   Updated: 2023/12/10 20:57:34 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int fd = open("textfile.txt", O_RDONLY);
	char *str;
	int i = 0;
	
	// printf("%s", str);
	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}