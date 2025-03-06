/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:01:31 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 17:40:28 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(t_data *data, int exit_status)
{
	if (data->cmd_count != 1)
	{
		free_all(data);
		close_error(0, data);
		close_error(1, data);
		exit(exit_status);
	}
	data->exit_status = exit_status;
}

void	exec_single_builtin(t_data *data)
{
	open_here_docs(data, data->tokens, 0);
	open_files(data, data->tokens, 0);
	if (data->open_fail == 1 || g_sig == SIGINT)
		return ;
	exec_builtin(data, 0);
	return ;
}

void	exec_builtin(t_data *data, int n)
{
	if (!ft_strncmp(data->instructions[n], "exit ", 5))
		exit_builtin(data, n);
	if (!ft_strncmp(data->instructions[n], "env ", 4))
		env_builtin(data);
	if (!ft_strncmp(data->instructions[n], "unset ", 6))
		unset_builtin(data, n);
	if (!ft_strncmp(data->instructions[n], "pwd ", 4))
		pwd_builtin(data);
	if (!ft_strncmp(data->instructions[n], "echo ", 5))
		echo_builtin(data, n);
	if (!ft_strncmp(data->instructions[n], "cd ", 3))
		cd_builtin(data, n);
	if (!ft_strncmp(data->instructions[n], "export ", 7))
		export_builtin(data, n);
	if (data->cmd_count == 1 && data->in_fds[0])
		close_error(data->in_fds[0], data);
	if (data->cmd_count == 1 && data->out_fds[0])
		close_error(data->out_fds[0], data);
}

int	is_builtin(t_data *data, int n)
{
	if (!data->instructions[n])
		return (0);
	if (!ft_strncmp(data->instructions[n], "exit ", 5)
		|| !ft_strncmp(data->instructions[n], "env ", 4)
		|| !ft_strncmp(data->instructions[n], "export ", 7)
		|| !ft_strncmp(data->instructions[n], "echo ", 5)
		|| !ft_strncmp(data->instructions[n], "pwd ", 4)
		|| !ft_strncmp(data->instructions[n], "cd ", 3)
		|| !ft_strncmp(data->instructions[n], "unset ", 6))
		return (1);
	return (0);
}
