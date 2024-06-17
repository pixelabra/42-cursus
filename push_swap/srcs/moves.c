/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:26:10 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:10 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rot_rot(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		rotate(stack1);
		rotate(stack2);
		ft_putendl_fd("rr", 1);
	}
	while (node->index)
	{
		rotate(stack1);
		ft_putendl_fd("ra", 1);
	}
	while (node->target->index)
	{
		rotate(stack2);
		ft_putendl_fd("rb", 1);
	}
}

void	rev_rev(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		reverse(stack1);
		reverse(stack2);
		ft_putendl_fd("rrr", 1);
	}
	while (node->index)
	{
		reverse(stack1);
		ft_putendl_fd("rra", 1);
	}
	while (node->target->index)
	{
		reverse(stack2);
		ft_putendl_fd("rrb", 1);
	}
}

void	rot_rev(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index)
	{
		rotate(stack1);
		ft_putendl_fd("ra", 1);
	}
	while (node->target->index)
	{
		reverse(stack2);
		ft_putendl_fd("rrb", 1);
	}
}

void	rev_rot(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index)
	{
		reverse(stack1);
		ft_putendl_fd("rra", 1);
	}
	while (node->target->index)
	{
		rotate(stack2);
		ft_putendl_fd("rb", 1);
	}
}

void	sort_three(t_node **stack)
{
	t_node	*absmax;

	if (!(*stack) || ps_lstsize(*stack) > 3)
		return ;
	absmax = abs_max(stack);
	if (absmax->index == 0)
	{
		rotate(stack);
		ft_putendl_fd("ra", 1);
	}
	else if (absmax->index == 1)
	{
		reverse(stack);
		ft_putendl_fd("rra", 1);
	}
	if (!issorted(stack))
	{
		swap(stack);
		ft_putendl_fd("sa", 1);
	}
}
