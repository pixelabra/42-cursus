/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:21:54 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 17:19:54 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig;

void	reset_data(t_data *data)
{
	g_sig = -1;
	data->input = NULL;
	data->instructions = NULL;
	data->tokens = NULL;
	data->env = NULL;
	data->in_fds = NULL;
	data->out_fds = NULL;
	data->pids = NULL;
	data->exit_status = 0;
	data->cmd_count = 0;
	data->prev_pipe_fd = -1;
	data->open_fail = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (1);
	(void)av;
	reset_data(&data);
	create_env(&data, env);
	if (!isatty(0))
		rl_outstream = stdin;
	take_input(&data);
	free_all(&data);
}
