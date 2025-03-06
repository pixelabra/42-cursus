/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:36:50 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 16:45:26 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->tokens)
		freelist(data->tokens);
	if (data->env)
		freelist(data->env);
	if (data->instructions)
		free_str_array(data->instructions, data->cmd_count);
	if (data->in_fds)
		free(data->in_fds);
	if (data->out_fds)
		free(data->out_fds);
	if (data->pids)
		free(data->pids);
}

void	free_str_array(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	if (!n)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
	}
	else if (n)
	{
		while (i < n)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
	}
	free(arr);
}

char	*ms_strjoin(char *s1, char *s2, int f, t_data *data)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ms_strdup(s2, data));
	if (!s2)
		return (ms_strdup(s1, data));
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	check_memory_failure(data, str, NULL, 1);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcpy(str + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	if (f == 1 && s1)
		free(s1);
	if (f == 2 && s2)
		free(s2);
	if (f == 3)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
	return (str);
}

char	*ms_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start > slen || !len)
		return (ft_strdup(""));
	if (start + len > slen)
		sub = ft_calloc(sizeof(char), (slen - start + 1));
	else
		sub = ft_calloc(sizeof(char), (len + 1));
	check_memory_failure(data, sub, NULL, 1);
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ms_strdup(const char *s, t_data *data)
{
	char		*dup;
	int			i;

	i = 0;
	dup = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	check_memory_failure(data, dup, NULL, 1);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}	
