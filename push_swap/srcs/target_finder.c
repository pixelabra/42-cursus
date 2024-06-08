/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:18:31 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/06 02:00:06 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <time.h>

t_node	*abs_min(t_node **stack)
{
	t_node	*temp;
	t_node	*ret_node;
	int		temp_nbr;

	if (!(*stack))
		return (NULL);
	ret_node = *stack;
	temp_nbr = ret_node->nbr;
	temp = (*stack)->next;
	while (temp)
	{
		if (temp_nbr > temp->nbr)
		{
			ret_node = temp;
			temp_nbr = temp->nbr;
		}
		temp = temp->next;
	}
	return (ret_node);
}

t_node	*abs_max(t_node **stack)
{
	t_node	*temp;
	t_node	*ret_node;
	int		temp_nbr;

	if (!(*stack))
		return (NULL);
	ret_node = *stack;
	temp_nbr = ret_node->nbr;
	temp = (*stack)->next;
	while (temp)
	{
		if (temp_nbr < temp->nbr)
		{
			ret_node = temp;
			temp_nbr = temp->nbr;
		}
		temp = temp->next;
	}
	return (ret_node);
}

t_node	*next_small(t_node **stack, int nbr)
{
	t_node	*temp;
	t_node	*ret_node;
	int		min;

	if (!(*stack))
		return (NULL);
	temp = *stack;
	ret_node = NULL;
	min = INT_MIN;
	while(temp)
	{
		if (temp->nbr < nbr && temp->nbr >= min)
		{
			min = temp->nbr;
			ret_node = temp;
		}
		temp = temp->next;
	}
	if (!ret_node)
		return (abs_max(stack));
	return (ret_node);
}

t_node	*next_big(t_node **stack, int nbr)
{
	t_node	*temp;
	t_node	*ret_node;
	int		max;

	if (!(*stack))
		return (NULL);
	temp = *stack;
	ret_node = NULL;
	max = INT_MAX;
	while(temp)
	{
		if (temp->nbr > nbr && temp->nbr <= max)
		{
			max = temp->nbr;
			ret_node = temp;
		}
		temp = temp->next;
	}
	if (!ret_node)
		return (abs_min(stack));
	return (ret_node);
}