/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:25:36 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:25:36 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	final_order(t_node **stack)
{
	t_node	*temp;
	int		size1;

	temp = abs_min(stack);
	size1 = ps_lstsize(*stack);
	if (issorted(stack))
		return ;
	while (temp->index)
	{
		if (temp->index < size1 / 2)
		{
			rotate(stack);
			ft_putendl_fd("ra", 1);
		}
		else if (temp->index >= size1 / 2)
		{
			reverse(stack);
			ft_putendl_fd("rra", 1);
		}
	}
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

void	algo_moves(t_node **stack1, t_node **stack2)
{
	t_node	*node;

	if (!(*stack1) || !(*stack2))
		return ;
	node = cheapest_node(stack1);
	if (node->flag == RotRot)
		rot_rot(node, stack1, stack2);
	else if (node->flag == RotRev)
		rot_rev(node, stack1, stack2);
	else if (node->flag == RevRot)
		rev_rot(node, stack1, stack2);
	else if (node->flag == RevRev)
		rev_rev(node, stack1, stack2);
	push(stack2, stack1);
	ft_putendl_fd("pb", 1);
}

void	algo_moves_back(t_node **stack1, t_node **stack2)
{
	t_node	*node;

	if (!(*stack1) || !(*stack2))
		return ;
	node = cheapest_node(stack2);
	if (node->flag == RotRot)
		rot_rot_back(node, stack1, stack2);
	else if (node->flag == RotRev)
		rot_rev_back(node, stack1, stack2);
	else if (node->flag == RevRot)
		rev_rot_back(node, stack1, stack2);
	else if (node->flag == RevRev)
		rev_rev_back(node, stack1, stack2);
	push(stack1, stack2);
	ft_putendl_fd("pa", 1);
}

void	push_push(t_node **stack1, t_node **stack2)
{
	int	size1;
	int	size2;

	push(stack2, stack1);
	ft_putendl_fd("pb", 1);
	if (ps_lstsize(*stack1) > 3)
	{
		push(stack2, stack1);
		ft_putendl_fd("pb", 1);
	}
	size1 = ps_lstsize(*stack1);
	while (size1-- > 3)
	{
		set_target_cost(stack1, stack2, 1);
		algo_moves(stack1, stack2);
	}
	sort_three(stack1);
	size2 = ps_lstsize(*stack2);
	while (size2-- > 0)
	{
		set_target_cost_back(stack1, stack2);
		algo_moves_back(stack1, stack2);
	}
	final_order(stack1);
}
