/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:33 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:17:42 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_dquotes_flag(char *str, int *dquote, int *squote, size_t *i)
{
	size_t	j;

	j = *i;
	if (str[j] == '\"' && *dquote == 1)
		*dquote = 0;
	else if (str[j] == '\"' && *dquote == 0 && squote && *squote == 0)
		*dquote = 1;
	else if (str[j] == '\"' && *dquote == 0 && !squote)
		*dquote = 1;
}

void	set_squotes_flag(char *str, int *squote, int *dquote, size_t *i)
{
	size_t	j;

	j = *i;
	if (str[j] == '\'' && *squote == 1)
		*squote = 0;
	else if (str[j] == '\'' && *squote == 0 && *dquote == 0)
		*squote = 1;
}

void	skip_single_quotes(char *str, int *dquote, int *squote, size_t *i)
{
	size_t	j;

	j = *i;
	set_dquotes_flag(str, dquote, squote, i);
	if (str[j] == '\'' && *dquote == 0)
	{
		j++;
		while (str[j] && str[j] != '\'')
			j++;
		if (str[j] && str[j] == '\'')
			j++;
	}
	*i = j;
}

char	*remove_quotes_extension(char *str, t_data *data)
{
	size_t	i;
	size_t	j;
	char	q;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	check_memory_failure(data, new, NULL, 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i++];
			while (str[i] && str[i] != q)
				new[j++] = str[i++];
			if (str[i] == q)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	free(str);
	return (new);
}

void	remove_quotes(t_data *data)
{
	t_dlist	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->str)
			temp->str = remove_quotes_extension(temp->str, data);
		temp = temp->next;
	}
}
