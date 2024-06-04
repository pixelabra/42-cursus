/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:37:41 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/04 17:07:48 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rot_rot(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		rotate(stack1);
		rotate(stack2);
		printf("rr\n");
	}
	while (node->index)
	{
		rotate(stack1);
		printf("ra\n");
	}
	while (node->target->index)
	{
		rotate(stack2);
		printf("rb\n");
	}
}

void	rev_rev(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index && node->target->index)
	{
		reverse(stack1);
		reverse(stack2);
		printf("rrr\n");
	}
	while (node->index)
	{
		reverse(stack1);
		printf("rra\n");
	}
	while (node->target->index)
	{
		reverse(stack2);
		printf("rrb\n");
	}
}

void	rot_rev(t_node *node, t_node **stack1, t_node **stack2, int size2)
{
	while (node->index)
	{
		rotate(stack1);
		printf("ra\n");
	}
	while (node->target->index)
	{
		reverse(stack2);
		printf("rrb\n");
	}
	(void) size2;
}

void	rev_rot(t_node *node, t_node **stack1, t_node **stack2, int size1)
{
	while (node->target->index)
	{
		rotate(stack2);
		printf("rb\n");
	}
	while (node->index)
	{
		reverse(stack1);
		printf("rra\n");
	}
	(void) size1;
}
