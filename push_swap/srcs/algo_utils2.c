/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:52:40 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/06 01:07:26 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	set_cost(t_node *node, int size1, int size2)
{
	// printf("Node: %d, Target: %d, Node Index: %d, Target Index: %d, Size1: %d, Size2: %d\n",
        //    node->nbr, node->target->nbr, node->index, node->target->index, size1, size2);
	if (!node)
		return ;
	if (node->target->index < size2 / 2 && node->index < size1 / 2)
	{
		node->cost = max_nbr(node->target->index, node->index);
		node->flag = RotRot;
	}
	else if (node->target->index < size2 / 2 && node->index >= size1 / 2)
	{
		node->cost = node->target->index + (size1 - node->index);
		node->flag = RevRot;
	}
	else if (node->target->index >= size2 / 2 && node->index < size1 / 2)
	{
		node->cost = (size2 - node->target->index) + node->index;
		node->flag = RotRev;
	}
	else if (node->target->index >= size2 / 2 && node->index >= size1 / 2)
	{
		node->cost = max_nbr(size2 - node->target->index, size1 - node->index);
		node->flag = RevRev;
	}
	// printf("Assigned Cost: %d, Flag: %d\n", node->cost, node->flag);
}

t_node	*cheapest_node(t_node **stack)
{
	t_node	*temp;
	t_node	*return_node;
	int		min_cost;

	if (!(*stack))
		return (NULL);
	return_node = *stack;
	temp = *stack;
	min_cost = temp->cost;
	while (temp)
	{
		if (temp->cost < min_cost)
		{
			return_node = temp;
			min_cost = temp->cost;
		}
		temp = temp->next;
	}
	return (return_node);
}

void	algo_moves(t_node **stack1, t_node **stack2, int flag)
{
	t_node	*node;

	if (!(*stack1) || !(*stack2))
		return ;
	if (flag)
		node = cheapest_node(stack1);
	else if (!flag)
		node = cheapest_node(stack2);
	if (node->flag == RotRot)
		rot_rot(node, stack1, stack2);
	else if (node->flag == RotRev)
		rot_rev(node, stack1, stack2, flag);
	else if (node->flag == RevRot)
		rev_rot(node, stack1, stack2, flag);
	else if (node->flag == RevRev)
		rev_rev(node, stack1, stack2);
	if (flag)
	{
		push(stack2, stack1);
		ft_putendl_fd("pb", 1);
	}
	if (!flag)
	{
		push(stack1, stack2);
		ft_putendl_fd("pa", 1);	
	}
}

void	push_push(t_node **stack1, t_node **stack2)
{
	int	size1;
	int	size2;

	push(stack2, stack1);
	ft_putendl_fd("pb", 1);
	push(stack2, stack1);
	ft_putendl_fd("pb", 1);
	size1 = ps_lstsize(*stack1);
	while (size1-- > 3)
	{
		set_target_cost(stack1, stack2, 1);
		algo_moves(stack1, stack2, 1);
	}
	sort_three(stack1);
	size2 = ps_lstsize(*stack2);
	// while (size2-- > 0)
	// {
	// 	set_target_cost(stack2, stack1, 0);
	// 	algo_moves(stack2, stack1, 0);
	// }
	push_back(stack1, stack2);
	(void) size2;
}
