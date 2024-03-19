/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:18:29 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/19 16:11:56 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int	fd[2];
	if (argc ==  5)
	{
		pipex(fd, argc, argv, envp);
		exit(0);
	}
	ft_putstr_fd("Input should be ./pipex infile cmd1 cmd2 outfile\n", 1);
	return (0);
}
