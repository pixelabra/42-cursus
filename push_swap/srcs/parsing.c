/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:18:53 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/30 00:02:39 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ps_error(void)
{
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
		ps_error();
	i = 0;
	temp = joined_arg;
	while (i < ac)
	{
		temp = ft_strlcpy;
	}
}

void	ps_stack_init(int ac, char **av, t_node **a)
{
	char	*joined_arg;

	joined_arg = ps_join_arg(ac, av);
}