/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arithmetic2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:56:03 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/03 23:08:43 by a3y3g1           ###   ########.fr       */
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
	(*stack)->prev = NULL;
	refresh_index(stack);
	return (temp);
}
