/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:21:58 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/21 23:19:45 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*px_strjoin(char *s1, char *s2)
{
	char	*str_join;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str_join = (char *) malloc(sizeof(char) * (len + 2));
	if (!str_join)
		return (NULL);
	*str_join = '\0';
	ft_strlcat(str_join, s1, len + 2);
	ft_strlcat(str_join, "/", len + 2);
	ft_strlcat(str_join, s2, len + 2);
	return (str_join);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths)
	{
		ft_putstr_fd("PATH not found\n", 2);
		exit(1);
	}
	return (paths);
}

void	check_access(char **arg_vect, char **envp)
{
	int		status;

	status = access(arg_vect[0], F_OK | X_OK);
	if (!status)
		return ;
	else
		getcmdpath(arg_vect, envp);
}

void	getcmdpath(char **arg_vect, char **envp)
{
	int		i;
	int		status;
	char	**paths;
	char	*temp_str;

	i = 0;
	status = 0;
	paths = get_paths(envp);
	while (paths && paths[i])
	{
		temp_str = px_strjoin(paths[i], arg_vect[0]);
		status = access(temp_str, F_OK | X_OK);
		if (!status)
		{
			free(arg_vect[0]);
			arg_vect[0] = ft_strdup(temp_str);
			free(temp_str);
			break ;
		}
		free(temp_str);
		i++;
	}
}

void	ft_error(int error_code)
{
	if (error_code == 1)
		exit(1);
}

void	exec_cmd(int i, char **envp, char **argv)
{
	char	**arg_vect;

	arg_vect = ft_split(argv[i], ' ');
	check_access(arg_vect, envp);
	execve(arg_vect[0], arg_vect, envp);
	ft_error(1);
}

void	io_dup(int i, int argc, char **argv, int fd[2])
{
	int	fd_infile;
	int	fd_outfile;

	if (i == 1)
	{
		close(fd[0]);
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile < 0)
			ft_error(1);
		dup2(fd_infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd_infile);
	}
	else if (i == argc - 3)
	{
		close(fd[1]);
		close(fd[0]);
		fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd_outfile < 0)
			ft_error(1);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}

void	inter_dup(pid_t pid, int fd[2])
{
	if (pid)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	pipex(int fd[2], int argc, char **argv, char **envp)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (++i < argc - 1)
	{
		if (pipe(fd) < 0)
			ft_error(1);
		pid = fork();
		if (pid < 0)
			ft_error(1);
		if (!pid)
		{
			if (i == 2 || i == argc - 2)
				io_dup(i - 1, argc, argv, fd);
			else
				inter_dup(pid, fd);
			exec_cmd(i, envp, argv);
		}
		if (i != argc - 2)
			inter_dup(pid, fd);
	}
}
