/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:18:53 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/30 02:12:45 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ps_error(char *ptr, char **dblptr)
{
	if (ptr)
		free(ptr);
	if (dblptr)
		free_dblptr(dblptr);
	ft_putendl_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

char	*ps_join_arg(int ac, char **av)
{
	int		i;
	size_t	length;
	char	*temp;
	char	*joined_arg;

	i = 0;
	length = 0;
	while (++i < ac)
		length += ft_strlen(av[i]) + 1;
	joined_arg = malloc(sizeof(char) * length);
	if (!joined_arg)
		ps_error(NULL, NULL);
	i = 0;
	temp = joined_arg;
	while (++i < ac)
	{
		ft_strlcpy(temp, av[i], ft_strlen(av[i]) + 1);
		temp += ft_strlen(av[i]);
		if (i < ac - 1)
			*temp++ = ' ';
	}
	*temp = '\0';
	return (joined_arg);
}

int	validate_numb(char *sep_arg)
{
	int		i;

	i = 0;
	if (sep_arg[i] == '-' || sep_arg[i] == '+')
		i++;
	if (!sep_arg[i])
		return (0);
	while (sep_arg[i])
	{
		if (!ft_isdigit(sep_arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ps_stack_init(int ac, char **av, t_node **a)
{
	int		i;
	char	*joined_arg;
	char	**sep_args;

	joined_arg = ps_join_arg(ac, av);
	sep_args = ft_split(joined_arg, ' ');
	free(joined_arg);
	if (!sep_args)
		ps_error(NULL, NULL);
	i = -1;
	while (sep_args[++i])
	{
		if (!validate_numb(sep_args[i]))
			ps_error(NULL, sep_args);
	}
	free_dblptr(sep_args);

	printf("GOOD\n");
	(void) a;
}