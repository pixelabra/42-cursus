/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_arithmetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 02:49:46 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/03 23:09:20 by a3y3g1           ###   ########.fr       */
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
	temp1->prev = temp1->next;
	temp1->next = temp2->next;
	*stack = temp2;
	temp2->next = temp1;
	temp2->prev = NULL;
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

// void rotate(t_node **stack) {
//     t_node *temp;

//     if (!(*stack) || ps_lstsize(*stack) < 2)
//         return ;
//     temp = *stack;
//     *stack = temp->next;
//     (*stack)->prev = NULL;

//     temp->next = NULL;
//     t_node *last = ps_lstlast(*stack);
//     last->next = temp;
//     temp->prev = last;
//     refresh_index(stack);
// }

// void reverse(t_node **stack) {
//     t_node *temp;

//     if (!(*stack) || ps_lstsize(*stack) < 2)
//         return ;
//     temp = ps_lstlast(*stack);
//     temp->prev->next = NULL;
//     temp->prev = NULL;
//     temp->next = *stack;
//     (*stack)->prev = temp;
//     *stack = temp;
//     refresh_index(stack);
// }
