/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:14:43 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 11:54:01 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

int	moves_cntnd(t_node **a, t_node **b, char *line)
{
	if (!ft_strncmp(line, "rr\n", 3))
	{
		rotate(a);
		rotate(b);
	}
	else if (!ft_strncmp(line, "rrr\n", 4))
	{
		reverse(a);
		reverse(b);
	}
	else
		return (1);
	return (0);
}

int	moves(t_node **a, t_node **b, char *line)
{
	if (!ft_strncmp(line, "pa\n", 3))
		push(b, a);
	else if (!ft_strncmp(line, "pb\n", 3))
		push(a, b);
	else if (!ft_strncmp(line, "ra\n", 3))
		rotate(a);
	else if (!ft_strncmp(line, "rb\n", 3))
		rotate(b);
	else if (!ft_strncmp(line, "sa\n", 3))
		swap(a);
	else if (!ft_strncmp(line, "sb\n", 3))
		swap(b);
	else if (!ft_strncmp(line, "rra\n", 4))
		reverse(a);
	else if (!ft_strncmp(line, "rrb\n", 4))
		reverse(b);
	else
		return (moves_cntnd(a, b, line));
	return (0);
}

void	apply_moves(t_node **a, t_node **b, char *line)
{
	while (line)
	{
		if (moves(a, b, line))
		{
			ps_lstclear(a);
			ps_lstclear(b);
			ps_error(line, NULL);
		}
		line = get_next_line(STDIN_FILENO);
	}
}

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;
	char	*line;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
	ps_stack_init(ac, av, &a);
	line = get_next_line(STDIN_FILENO);
	apply_moves(&a, &b, line);
	if (!issorted(&a))
		ft_putendl_fd("KO", 2);
	else if (issorted(&a))
		ft_putendl_fd("OK", 1);
	ps_lstclear(&a);
	ps_lstclear(&b);
	return (0);
}
