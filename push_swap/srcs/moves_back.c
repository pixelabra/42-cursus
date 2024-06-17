/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:26:03 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:03 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rot_rot_back(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		rotate(stack1);
		rotate(stack2);
		ft_putendl_fd("rr", 1);
	}
	while (node->target->index)
	{
		rotate(stack1);
		ft_putendl_fd("ra", 1);
	}
	while (node->index)
	{
		rotate(stack2);
		ft_putendl_fd("rb", 1);
	}
}

void	rev_rev_back(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		reverse(stack1);
		reverse(stack2);
		ft_putendl_fd("rrr", 1);
	}
	while (node->target->index)
	{
		reverse(stack1);
		ft_putendl_fd("rra", 1);
	}
	while (node->index)
	{
		reverse(stack2);
		ft_putendl_fd("rrb", 1);
	}
}

void	rot_rev_back(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->target->index)
	{
		rotate(stack1);
		ft_putendl_fd("ra", 1);
	}
	while (node->index)
	{
		reverse(stack2);
		ft_putendl_fd("rrb", 1);
	}
}

void	rev_rot_back(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->target->index)
	{
		reverse(stack1);
		ft_putendl_fd("rra", 1);
	}
	while (node->index)
	{
		rotate(stack2);
		ft_putendl_fd("rb", 1);
	}
}
