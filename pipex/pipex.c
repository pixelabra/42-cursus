/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:18:29 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/02 20:31:19 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 1;
	while (++i < argc - 1)
	{
		if (pipe(fd) < 0)
			ft_error(1, NULL);
		pid = fork();
		if (pid < 0)
			ft_error(2, NULL);
		if (!pid)
		{
			if (i == 2 || i == argc - 2)
				io_dup(i - 1, argc, argv, fd);
			else
				inter_dup(pid, fd);
			exec_cmd(i, envp, argv);
		}
		inter_dup(pid, fd);
	}
	termination_check(pid);
}

int	main(int argc, char **argv, char **envp)
{
	if (!envp || !*envp)
		ft_error(6, NULL);
	if (argc == 5)
	{
		pipex(argc, argv, envp);
		exit(0);
	}
	ft_putstr_fd("Input should be ./pipex infile cmd1 cmd2 outfile\n", 1);
	return (0);
}
