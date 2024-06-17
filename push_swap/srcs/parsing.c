/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:26:17 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:17 by agodeanu         ###   ########.fr       */
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
		ps_error(NULL, NULL, NULL);
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

void	isvalidnbr(char *sep_arg, char **sep_args, t_node *node)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = node;
	if (sep_arg[i] == '-' || sep_arg[i] == '+')
		i++;
	if (!sep_arg[i])
	{
		ps_lstclear(&temp);
		ps_error(NULL, sep_args, NULL);
	}
	while (sep_arg[i])
	{
		if (!ft_isdigit(sep_arg[i]))
		{
			ps_lstclear(&temp);
			ps_error(NULL, sep_args, NULL);
		}
		i++;
	}
}

void	isduplicate(t_node *lst)
{
	t_node	*temp_fast;
	t_node	*temp_slow;

	if (!lst)
		ps_error_lst(&lst, NULL);
	temp_slow = lst;
	while (temp_slow)
	{
		temp_fast = temp_slow->next;
		while (temp_fast)
		{
			if (temp_slow->nbr == temp_fast->nbr)
				ps_error_lst(&lst, NULL);
			temp_fast = temp_fast->next;
		}
		temp_slow = temp_slow->next;
	}
}

long	ps_atol(char *sep_arg, char **sep_args, t_node **a)
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
			ps_error(NULL, sep_args, a);
		nbr = (nbr * 10) + (sep_arg[i++] - '0');
	}
	nbr *= sign;
	if (nbr > INT_MAX || nbr < INT_MIN)
		ps_error(NULL, sep_args, a);
	return (nbr);
}

void	ps_stack_init(int ac, char **av, t_node **a)
{
	int		i;
	long	nbr;
	char	*joined_arg;
	char	**sep_args;
	t_node	*new_node;

	isemptyargs(ac, av);
	joined_arg = ps_join_arg(ac, av);
	sep_args = ft_split(joined_arg, ' ');
	free(joined_arg);
	if (!sep_args)
		ps_error(NULL, NULL, NULL);
	i = -1;
	while (sep_args[++i])
	{
		nbr = ps_atol(sep_args[i], sep_args, a);
		new_node = ps_lstnew(nbr, i);
		if (!new_node)
			ps_error(NULL, sep_args, NULL);
		ps_lstadd_back(a, new_node);
		isvalidnbr(sep_args[i], sep_args, *a);
	}
	free_dblptr(sep_args);
	isduplicate(*a);
}
