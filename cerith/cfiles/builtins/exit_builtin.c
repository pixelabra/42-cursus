/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:24 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:12:26 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_builtin_no_params(t_data *data, char **params)
{
	ft_putendl_fd("exit", 2);
	free_str_array(params, 0);
	free_all(data);
	exit(0);
}

void	exit_builtin_invalid_params(t_data *data, char **params)
{
	ft_putstr_fd(SHELLNAME"exit: ", 2);
	ft_putstr_fd(params[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_str_array(params, 0);
	free_all(data);
	exit(255);
}

void	exit_builtin(t_data *data, int n)
{
	char		**params;
	long long	code;

	params = create_exec_array(data, n);
	if (!params[1])
		exit_builtin_no_params(data, params);
	if (params[1] && !checkfornum(params[1]))
		exit_builtin_invalid_params(data, params);
	if (params[2])
	{
		error("exit: too many arguments", NULL, data);
		free_str_array(params, 0);
		builtin_exit(data, 1);
		return ;
	}
	if (params[1] && checkfornum(params[1]))
	{
		code = ft_atol(params[1]);
		ft_putendl_fd("exit", 2);
		free_str_array(params, 0);
		free_all(data);
		exit(code);
	}
}
