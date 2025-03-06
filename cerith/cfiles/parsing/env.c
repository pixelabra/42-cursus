/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:09:33 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:16:07 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var_str(char *str, t_data *data)
{
	size_t	i;
	t_dlist	*temp;
	char	*itoa;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '?' || str[0] == '$')
		i++;
	else
		while (!check_invalid_chars_env_var(str[i]))
			i++;
	if (i)
	{
		if (str[0] == '?')
		{
			itoa = ft_itoa(data->exit_status);
			check_memory_failure(data, itoa, NULL, 1);
			return (itoa);
		}
		temp = get_env_var(ms_substr(str, 0, i, data), data->env);
		if (temp)
			return (ms_strdup(temp->str + i + 1, data));
	}
	return (NULL);
}

t_dlist	*get_env_var(char *var, t_dlist *env)
{
	t_dlist	*temp;

	temp = env;
	while (temp)
	{
		if (!cmp_up_to_equal(var, temp->str))
		{
			free(var);
			return (temp);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}

char	*find_path_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*search_path(char *cmd, char **env, t_data *data)
{
	char	**env_words;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (cmd);
	i = -1;
	env_words = ft_split(find_path_in_env(env), ':');
	if (!env_words)
		return (cmd);
	while (env_words[++i])
	{
		path = ms_strjoin(env_words[i], "/", 0, data);
		path = ms_strjoin(path, cmd, 1, data);
		if (!access(path, X_OK | F_OK))
		{
			free_str_array(env_words, 0);
			free(cmd);
			return (path);
		}
		free(path);
	}
	free_str_array(env_words, 0);
	return (cmd);
}

char	**convert_env_to_strings(t_data *data)
{
	int		i;
	t_dlist	*temp;
	char	**env;

	i = 0;
	temp = data->env;
	env = NULL;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			i++;
		temp = temp->next;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	check_memory_failure(data, NULL, env, 2);
	i = 0;
	temp = data->env;
	while (temp)
	{
		if (ft_strchr(temp->str, '='))
			env[i++] = ms_strdup(temp->str, data);
		temp = temp->next;
	}
	return (env);
}
