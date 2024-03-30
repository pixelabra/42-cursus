/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:59:52 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/30 18:20:32 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_input_hdc(char **argv, int fd[2])
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2]))
			&& ft_strlen(line) - 1 == ft_strlen(argv[2]))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

void	io_dup_hdc(int i, int argc, char **argv, int fd[2])
{
	int		fd_outfile;

	if (i == 2)
	{
		get_input_hdc(argv, fd);
		close(fd[1]);
		if (dup_check(fd[0], STDIN_FILENO) < 0)
			ft_error(4, NULL);
	}
	else if (i == argc - 3)
	{
		close(fd[1]);
		close(fd[0]);
		fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd_outfile < 0)
			ft_error(3, argv[argc - 1]);
		if (dup_check(fd_outfile, STDOUT_FILENO) < 0)
			ft_error(4, NULL);
	}
}

void	pipex_hdc(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 2;
	while (++i < argc - 1)
	{
		if (pipe(fd) < 0)
			ft_error(1, NULL);
		pid = fork();
		if (pid < 0)
			ft_error(2, NULL);
		if (!pid)
		{
			if (i == 3 || i == argc - 2)
				io_dup_hdc(i - 1, argc, argv, fd);
			else
				inter_dup(pid, fd);
			exec_cmd(i, envp, argv);
		}
		if (i != argc - 2)
			inter_dup(pid, fd);
	}
	termination_check(pid);
}
