/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:46:38 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/06 02:02:41 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	set_target_cost(t_node **stack1, t_node **stack2, int flag)
{
	t_node	*temp;
	int		size1;
	int		size2;

	if (!(*stack1) || !(*stack2))
		return ;
	temp = *stack1;
	size1 = ps_lstsize(*stack1);
	size2 = ps_lstsize(*stack2);
	while (temp)
	{
		if (flag)
			temp->target = next_small(stack2, temp->nbr);
		else if (!flag)
			temp->target = next_big(stack2, temp->nbr);
		if (flag)
			set_cost(temp, size1, size2);
		else if (!flag)
			set_cost(temp, size2, size1);
		temp = temp->next;
	}
}

void	set_target_cost_back(t_node **stack1, t_node **stack2)
{
	t_node	*temp;
	int		size1;
	int		size2;

	if (!(*stack1) || !(*stack2))
		return ;
	temp = *stack2;
	size1 = ps_lstsize(*stack1);
	size2 = ps_lstsize(*stack2);
	while (temp)
	{
		temp->target = next_big(stack1, temp->nbr);
		set_cost_back(temp, size1, size2);
		temp = temp->next;
	}
}

void	set_cost(t_node *node, int size1, int size2)
{
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
}

void	set_cost_back(t_node *node, int size1, int size2)
{
	if (!node)
		return ;
	if (node->target->index < size1 / 2 && node->index < size2 / 2)
	{
		node->cost = max_nbr(node->target->index, node->index);
		node->flag = RotRot;
	}
	else if (node->target->index < size1 / 2 && node->index >= size2 / 2)
	{
		node->cost = node->target->index + (size2 - node->index);
		node->flag = RotRev;
	}
	else if (node->target->index >= size1 / 2 && node->index < size2 / 2)
	{
		node->cost = (size1 - node->target->index) + node->index;
		node->flag = RevRot;
	}
	else if (node->target->index >= size1 / 2 && node->index >= size2 / 2)
	{
		node->cost = max_nbr(size1 - node->target->index, size2 - node->index);
		node->flag = RevRev;
	}
}
