/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_executing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:21:58 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/31 17:38:00 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	io_dup(int i, int argc, char **argv, int fd[2])
{
	int	fd_infile;
	int	fd_outfile;

	if (i == 1)
	{
		close(fd[0]);
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile < 0)
			ft_error(3, argv[1]);
		if (dup_check(fd_infile, STDIN_FILENO) < 0
			|| dup_check(fd[1], STDOUT_FILENO) < 0)
			ft_error(4, NULL);
	}
	else if (i == argc - 3)
	{
		close(fd[1]);
		close(fd[0]);
		fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd_outfile < 0)
			ft_error(3, argv[argc - 1]);
		if (dup_check(fd_outfile, STDOUT_FILENO) < 0)
			ft_error(4, NULL);
	}
}

void	inter_dup(pid_t pid, int fd[2])
{
	if (pid)
	{
		close(fd[1]);
		if (dup_check(fd[0], STDIN_FILENO) < 0)
			ft_error(4, NULL);
	}
	else if (!pid)
	{
		close(fd[0]);
		if (dup_check(fd[1], STDOUT_FILENO) < 0)
			ft_error(4, NULL);
	}
}

int	dup_check(int oldfd, int newfd)
{
	int	status;

	status = dup2(oldfd, newfd);
	close(oldfd);
	return (status);
}

void	check_access(char **arg_vect, char **envp)
{
	int		status;

	status = access(arg_vect[0], F_OK | X_OK);
	if (!status)
		return ;
	else
		getcmdpath(arg_vect, envp, 0, 0);
}

void	exec_cmd(int i, char **envp, char **argv)
{
	char	**arg_vect;
	int		j;

	arg_vect = ft_split(argv[i], ' ');
	check_access(arg_vect, envp);
	execve(arg_vect[0], arg_vect, envp);
	j = -1;
	ft_error(5, arg_vect[0]);
	while (arg_vect[++j])
		free(arg_vect[j]);
	free(arg_vect);
	exit(127);
}
