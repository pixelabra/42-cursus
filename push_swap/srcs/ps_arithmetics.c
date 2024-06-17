/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arithmetics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:26:23 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:23 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_node **stack)
{
	t_node	*temp1;
	t_node	*temp2;

	if (ps_lstsize(*stack) <= 1)
		return ;
	temp1 = *stack;
	temp2 = (*stack)->next;
	if (temp2->next)
		temp2->next->prev = temp1;
	temp1->next = temp2->next;
	temp2->next = temp1;
	temp2->prev = temp1->prev;
	temp1->prev = temp2;
	*stack = temp2;
	refresh_index(stack);
}

void	push(t_node **pushee, t_node **pusher)
{
	t_node	*temp;

	if (!(*pusher))
		return ;
	temp = pop(pusher);
	ps_lstadd_front(pushee, temp);
	refresh_index(pusher);
	refresh_index(pushee);
}

void	rotate(t_node **stack)
{
	t_node	*temp;

	if (!(*stack) || ps_lstsize(*stack) < 2)
		return ;
	temp = pop(stack);
	ps_lstadd_back(stack, temp);
	refresh_index(stack);
}

void	reverse(t_node **stack)
{
	t_node	*temp;

	if (!(*stack) || ps_lstsize(*stack) < 2)
		return ;
	temp = ps_lstlast(*stack);
	temp->prev->next = NULL;
	ps_lstadd_front(stack, temp);
	refresh_index(stack);
}
