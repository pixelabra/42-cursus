/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:39:11 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/05 16:51:22 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_tokens(t_data *data)
{
	t_dlist	*temp;

	temp = data->tokens;
	while (temp)
	{
		if ((check_token_redir(temp) || temp->token == HERE_DOC)
			&& !temp->next)
			return (error("syntax error near unexpected token: ",
					"\'newline\'", data));
		if (((temp->index == 0 || temp->index == listsize(data->tokens) - 1)
				&& (temp->token == PIPE)) || (temp->token == PIPE
				&& temp->next && temp->next->token == PIPE)
			|| (check_token_redir(temp) && check_token_redir(temp->next))
			|| (temp->token == HERE_DOC && temp->next
				&& temp->next->token == HERE_DOC) || (temp->token == HERE_DOC
				&& temp->next && temp->next->token != LIMITER)
			|| ((check_token_redir(temp) || temp->token == HERE_DOC)
				&& temp->next && temp->next->token == PIPE))
			return (error("syntax error near unexpected token: ",
					temp->str, data));
		if (temp->token == UNKNOWN)
			return (error("unrecognized token: ", temp->str, data));
		temp = temp->next;
	}
	return (0);
}

void	set_types_extension(t_dlist *temp)
{
	if ((temp->index == 0)
		|| (temp->prev && temp->prev->token == PIPE)
		|| (temp->prev && !check_for_cmd(temp)
			&& (temp->prev->token == FILENAME
				|| temp->prev->token == LIMITER)))
		temp->token = CMD;
	else if (temp->prev
		&& check_for_cmd(temp) && !check_token_redir(temp->prev)
		&& (temp->prev->token == FILENAME || temp->prev->token == CMD
			|| temp->prev->token == LIMITER || temp->prev->token == PARAM))
		temp->token = PARAM;
	else if (temp->prev
		&& check_token_redir(temp->prev))
		temp->token = FILENAME;
	else
		temp->token = UNKNOWN;
}

void	set_types(t_dlist **tokens)
{
	t_dlist	*temp;

	temp = *tokens;
	while (temp)
	{
		if (!ft_strncmp(temp->str, "|", 2))
			temp->token = PIPE;
		else if (!ft_strncmp(temp->str, ">", 2))
			temp->token = OUTF;
		else if (!ft_strncmp(temp->str, "<", 2))
			temp->token = INF;
		else if (!ft_strncmp(temp->str, "<<", 3))
			temp->token = HERE_DOC;
		else if (!ft_strncmp(temp->str, ">>", 3))
			temp->token = OUTF_APD;
		else if (temp->prev && temp->prev->token == HERE_DOC)
			temp->token = LIMITER;
		else
			set_types_extension(temp);
		temp = temp->next;
	}
}

char	*get_word(char *input, size_t *i, t_data *data)
{
	size_t	j;
	char	q;

	j = 0;
	while (input[j] && (is_whitespace(input[j])))
	{
		input++;
		*(i) += 1;
	}
	if (!input[j])
		return (NULL);
	while (input[j] && (!is_whitespace(input[j])))
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			q = input[j++];
			while (input[j] != q)
				j++;
		}
		if (input[j])
			j++;
	}
	return (ms_substr(input, 0, j, data));
}

void	create_token_list(char *input, t_data *data)
{
	char	*word;
	size_t	i;
	t_dlist	*temp;

	i = 0;
	while (1)
	{
		word = get_word(input + i, &i, data);
		if (!word)
			break ;
		temp = newnode(word);
		check_memory_failure(data, temp, NULL, 1);
		node_addback(&data->tokens, temp);
		i += ft_strlen(word);
	}
	set_types(&data->tokens);
}
