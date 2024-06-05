/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arithmetic2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:56:03 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/04 21:56:41 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	max_nbr(int nbr1, int nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}

void	refresh_index(t_node **stack)
{
	int		i;
	t_node	*temp;

	if (!(*stack))
		return ;
	i = 0;
	temp = *stack;
	while (temp)
	{
		temp->index = i;
		temp = temp->next;
		i++;
	}
}

t_node	*pop(t_node **stack)
{
	t_node	*temp;

	if (!(*stack))
		return (NULL);
	temp = *stack;
	*stack = temp->next;
	temp->next = NULL;
	if (*stack)
		(*stack)->prev = NULL;
	refresh_index(stack);
	return (temp);
}

int	issorted(t_node **stack)
{
	t_node	*temp;
	t_node	*temp_next;
	

	if (!(*stack))
		return (-1);
	temp = *stack;
	temp_next = temp->next;
	while (temp_next)
	{
		if (temp_next->nbr < temp->nbr)
			return (0);
		temp = temp->next;
		temp_next = temp->next;
	}
	return (1);
}
