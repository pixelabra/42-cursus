/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:34:06 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:11:57 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(t_data *data, int n)
{
	t_dlist	*temp;
	char	**params;
	int		i;

	params = create_exec_array(data, n);
	i = 1;
	while (params[i])
	{
		temp = get_env_var(ms_strdup(params[i], data), data->env);
		if (temp)
		{
			if (!temp->prev)
				data->env = temp->next;
			if (temp->prev)
				temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			if (temp->str)
				free(temp->str);
			free(temp);
		}
		i++;
	}
	free_str_array(params, 0);
	builtin_exit(data, 0);
}

void	env_builtin(t_data *data)
{
	t_dlist	*temp;
	int		fd;

	if (data->cmd_count == 1 && data->out_fds[0])
		fd = data->out_fds[0];
	else
		fd = 1;
	temp = data->env;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			ft_putendl_fd(temp->str, fd);
		temp = temp->next;
	}
	builtin_exit(data, 0);
}
