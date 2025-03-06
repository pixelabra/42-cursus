/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:36:52 by ppolinta          #+#    #+#             */
/*   Updated: 2025/03/05 13:16:36 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_exp_len_extension(char *str, t_data *data, size_t *len)
{
	char	*env_var;

	env_var = get_env_var_str(str, data);
	if (!env_var)
		*len -= (env_var_name_len(str)) + 1;
	else
	{
		*len += ft_strlen(env_var);
		*len -= (env_var_name_len(str)) + 1;
		free(env_var);
	}
}

size_t	get_exp_len(char *str, t_data *data)
{
	size_t	i;
	size_t	len;
	int		dquote;

	i = 0;
	dquote = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		skip_single_quotes(str, &dquote, NULL, &i);
		if (str[i] == '$' && (!check_invalid_chars_env_var(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '$'))
		{
			get_exp_len_extension(str + i + 1, data, &len);
			i++;
		}
		if (str[i])
			i++;
	}
	return (len);
}

int	check_invalid_chars_env_var(char c)
{
	if (c != '_' && !(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z') && !(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

size_t	env_var_name_len(char *str)
{
	size_t	var_len;

	var_len = 0;
	if (ft_isdigit(str[0]) || str[0] == '?' || str[0] == '$')
		var_len++;
	else
		while (!check_invalid_chars_env_var(str[var_len]))
			var_len++;
	return (var_len);
}
