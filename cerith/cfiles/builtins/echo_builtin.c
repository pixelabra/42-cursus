/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:29:21 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:11:25 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	echo_newline_flag(char **params, int *newline)
{
	size_t	i;
	size_t	j;

	i = 1;
	*newline = 1;
	while (params[i])
	{
		j = 0;
		if (params[i][j] == '-' && params[i][j + 1])
		{
			j++;
			while (params[i][j] && params[i][j] == 'n')
				j++;
			if (!params[i][j])
				*newline = 0;
			else
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

void	echo_builtin(t_data *data, int n)
{
	char	**params;
	size_t	i;
	int		fd;
	int		newline;

	params = create_exec_array(data, n);
	if (data->cmd_count == 1 && data->out_fds[0])
		fd = data->out_fds[0];
	else
		fd = 1;
	i = echo_newline_flag(params, &newline);
	while (params[i])
	{
		ft_putstr_fd(params[i], fd);
		if (params[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
	free_str_array(params, 0);
	builtin_exit(data, 0);
}
