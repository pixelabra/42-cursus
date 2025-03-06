/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:02:15 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:13:05 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_fail(char *cmd, char **execve_arr, char **env, t_data *data)
{
	ft_putstr_fd(SHELLNAME, 2);
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": Command not found", 2);
	free(cmd);
	free_str_array(env, 0);
	free_str_array(execve_arr, 0);
	free_all(data);
	close_error(0, data);
	close_error(1, data);
}

void	exec_single_cmd(t_data *data, int n)
{
	char	**execve_arr;
	char	**env;
	char	*cmd;

	if (!data->instructions[n])
		return ;
	if (is_builtin(data, n))
		exec_builtin(data, n);
	else
	{
		execve_arr = create_exec_array(data, n);
		env = convert_env_to_strings(data);
		cmd = ms_strdup(execve_arr[0], data);
		execve_arr[0] = search_path(execve_arr[0], env, data);
		execve(execve_arr[0], execve_arr, env);
		execve_fail(cmd, execve_arr, env, data);
	}
	exit(127 - (errno == EACCES));
}

void	execution_child(t_data *data, int i)
{
	signal(SIGQUIT, SIG_DFL);
	open_files(data, data->tokens, i);
	dupdup(data, i);
	exec_single_cmd(data, i);
}

void	execution_parent(t_data *data, int i)
{
	signal(SIGINT, do_nothing);
	data->pids[i] = fork();
	if (data->pids[i] == 0)
		execution_child(data, i);
	else if (data->pids[i] < 0)
		ms_perror(data);
	if (data->in_fds[i])
		close_error(data->in_fds[i], data);
	if (i < data->cmd_count - 1)
		close_error(data->pipe_fds[1], data);
	if (data->prev_pipe_fd != -1)
		close_error(data->prev_pipe_fd, data);
	if (data->cmd_count > 1)
		data->prev_pipe_fd = data->pipe_fds[0];
}

void	execution(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count && g_sig != SIGINT)
	{
		open_here_docs(data, data->tokens, i);
		if (g_sig == SIGINT)
		{
			if (data->in_fds[i])
				close_error(data->in_fds[i], data);
			break ;
		}
		if (i < data->cmd_count - 1)
			if (pipe(data->pipe_fds) < 0)
				ms_perror(data);
		execution_parent(data, i);
		i++;
	}
	if (g_sig == SIGINT)
		data->exit_status = 130;
	else
		exit_status(data->pids[i - 1], data);
	g_sig = -1;
}
