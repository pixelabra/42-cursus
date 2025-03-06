/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:40:04 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 17:29:36 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if quotes were not closed.
int	check_quotes(char *input)
{
	char	q;
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			q = input[i++];
			while (input[i] && input[i] != q)
				i++;
			if (!input[i])
				return (1);
		}
		i++;
	}
	return (0);
}

void	expand_all_tokens(t_data *data)
{
	t_dlist	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->token != LIMITER)
			temp->str = expand_env_vars(temp->str, data);
		temp = temp->next;
	}
}

int	check_empty_input(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (!input[i] || !ft_strncmp(input, "", 1))
		return (1);
	return (0);
}

int	parse_input(t_data *data)
{
	if (check_empty_input(data->input))
		return (1);
	add_history(data->input);
	if (check_quotes(data->input))
	{
		data->exit_status = 258;
		return (error("syntax error: unclosed quotations", NULL, data));
	}
	data->input = fix_input(data->input, data);
	create_token_list(data->input, data);
	if (parse_tokens(data))
	{
		data->exit_status = 258;
		return (1);
	}
	expand_all_tokens(data);
	remove_quotes(data);
	convert_tokens(data);
	return (0);
}
