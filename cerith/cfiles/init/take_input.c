/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:25:27 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:15:41 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_input(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->in_fds)
		free(data->in_fds);
	if (data->out_fds)
		free(data->out_fds);
	if (data->pids)
		free(data->pids);
	freelist(data->tokens);
	if (data->instructions)
		free_str_array(data->instructions, data->cmd_count);
	data->cmd_count = 0;
	data->prev_pipe_fd = -1;
	data->open_fail = 0;
	data->input = NULL;
	data->tokens = NULL;
	data->instructions = NULL;
	data->in_fds = NULL;
	data->out_fds = NULL;
	data->pids = NULL;
}

void	take_input(t_data *data)
{
	while (1)
	{
		signal(SIGINT, readline_sig);
		signal(SIGQUIT, SIG_IGN);
		data->input = readline(SHELLPRMPT);
		if (g_sig == SIGINT)
			data->exit_status = 1;
		g_sig = -1;
		if (!data->input)
			break ;
		if (!parse_input(data))
		{
			alloc_fd_pid_arrays(data);
			if (data->cmd_count == 1 && is_builtin(data, 0))
				exec_single_builtin(data);
			else
				execution(data);
		}
		reset_input(data);
	}
}
