/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:18:53 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/30 22:31:50 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

void	isvalidnbr(char *sep_arg, char **sep_args)
{
	int		i;

	i = 0;
	if (sep_arg[i] == '-' || sep_arg[i] == '+')
		i++;
	if (!sep_arg[i])
		ps_error(NULL, sep_args);
	while (sep_arg[i])
	{
		if (!ft_isdigit(sep_arg[i]))
			ps_error(NULL, sep_args);
		i++;
	}
}

long	ps_atol(char *sep_arg, char **sep_args)
{
	int			i;
	long		sign;
	long long	nbr;

	i = 0;
	nbr = 0;
	sign = 1;
	if (sep_arg[i] == '-' || sep_arg[i] == '+')
	{
		if (sep_arg[i] == '-')
			sign *= -1;
		i++;
	}
	while (sep_arg[i] && sep_arg[i] >= '0' && sep_arg[i] <= '9')
	{
		if ((nbr > LONG_MAX / 10)
			|| (nbr == LONG_MAX / 10 && sep_arg[i] > '7'))
			ps_error(NULL, sep_args);
		nbr = (nbr * 10) + (sep_arg[i++] - '0');
	}
	nbr *= sign;
	if (nbr > INT_MAX || nbr < INT_MIN)
		ps_error(NULL, sep_args);
	return (nbr);
}

void	ps_stack_init(int ac, char **av, t_node **a)
{
	int		i;
	long	nbr;
	char	*joined_arg;
	char	**sep_args;
	t_node	*new_node;

	joined_arg = ps_join_arg(ac, av);
	sep_args = ft_split(joined_arg, ' ');
	free(joined_arg);
	if (!sep_args)
		ps_error(NULL, NULL);
	i = -1;
	while (sep_args[++i])
	{
		isvalidnbr(sep_args[i], sep_args);
		nbr = ps_atol(sep_args[i], sep_args);
		printf("%ld\n", nbr);
	}
	free_dblptr(sep_args);
	printf("GOOD\n");
	(void) a;
	(void) new_node;
}
