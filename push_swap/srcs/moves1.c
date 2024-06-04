/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:37:41 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/03 20:34:32 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rot_rot(t_node *node, t_node **stack1, t_node **stack2)
{
	while (node->index > 0 && node->target->index > 0)
	{
		rotate(stack1);
		rotate(stack2);
		printf("rr\n");
		node->index--;
		node->target->index--;
	}
	while (node->index > 0)
	{
		rotate(stack1);
		printf("ra\n");
		node->index--;
	}
	while (node->target->index > 0)
	{
		rotate(stack2);
		printf("rb\n");
		node->target->index--;
	}
}

void	rev_rev(t_node *node, t_node **stack1, t_node **stack2)
{
	int	size1;
	int	size2;

	size1 = ps_lstsize(*stack1);
	size2 = ps_lstsize(*stack2);
	while (node->index < size1 && node->target->index < size2)
	{
		reverse(stack1);
		reverse(stack2);
		printf("rrr\n");
		node->index++;
		node->target->index++;
	}
	while (node->index < size1)
	{
		reverse(stack1);
		printf("ra\n");
		node->index++;
	}
	while (node->target->index < size2)
	{
		reverse(stack2);
		printf("rb\n");
		node->target->index++;
	}
}

void	rot_rev(t_node *node, t_node **stack1, t_node **stack2, int size2)
{
	while (node->index > 0)
	{
		rotate(stack1);
		printf("ra\n");
		node->index--;
	}
	while (node->target->index < size2)
	{
		reverse(stack2);
		printf("rrb\n");
		node->target->index++;
	}
}

void	rev_rot(t_node *node, t_node **stack1, t_node **stack2, int size1)
{
	while (node->index < size1)
	{
		reverse(stack1);
		printf("rra\n");
		node->index++;
	}
	while (node->target->index > 0)
	{
		rotate(stack2);
		printf("rb\n");
		node->target->index--;
	}
}
