/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_parsing_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:27:58 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/30 21:04:27 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		exit(EXIT_FAILURE);
	}
	return (paths);
}

void	getcmdpath(char **arg_vect, char **envp, int i, int status)
{
	char	**paths;
	char	*temp_str;

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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

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

void	ft_error(int error_code, char *str)
{
	if (error_code == 1)
		perror("pipe");
	else if (error_code == 2)
		perror("fork");
	else if (error_code == 3)
		perror(str);
	else if (error_code == 4)
		perror("dup2");
	else if (error_code == 5)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	else if (error_code == 6)
		ft_putstr_fd("No environment\n", 1);
	exit(EXIT_FAILURE);
}

void	termination_check(pid_t pid)
{
	pid_t	temp;
	int		status;
	int		wstatus;

	status = 0;
	while (1)
	{
		temp = wait(&wstatus);
		if (temp == pid)
		{
			status = wstatus;
			break ;
		}
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}
