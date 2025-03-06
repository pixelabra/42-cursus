/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:21:57 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/05 17:00:10 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '-') || (c == '.')
		|| (c == '/') || (c == '_') || (c == ',') || (c == ':')
		|| (c == '$') || (c == '\"') || (c == '\'') || (c == '+'))
		return (1);
	return (0);
}

// Checks if the received token is a redirection token, excluding here_doc.
int	check_token_redir(t_dlist *node)
{
	if (!node)
		return (0);
	if (node->token == INF || node->token == OUTF
		|| node->token == OUTF_APD)
		return (1);
	return (0);
}

// Checks if there was previously a command token in the list up to
// where the received token is and until a pipe is encountered.
int	check_for_cmd(t_dlist *node)
{
	node = node->prev;
	if (node->token == PIPE)
		return (0);
	while (node && node->token != PIPE)
	{
		if (node->token == CMD)
			return (1);
		node = node->prev;
	}
	return (0);
}
