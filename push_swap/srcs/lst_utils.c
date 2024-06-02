/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:33:23 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/02 22:51:55 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ps_lstnew(int nbr, int i)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->nbr = nbr;
	new_node->cost = 0;
	new_node->index = i;
	new_node = 0;
	new_node->target = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_node *ps_lstlast(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ps_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	last = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ps_lstlast(*lst);
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

void	ps_lstadd_front(t_node **lst, t_node *new)
{
	if (!(*lst))
		*lst = new;
	else
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
		new->prev = NULL;
	}
}

int	ps_lstsize(t_node *lst)
{
	int		size;
	t_node	*temp;

	size = 0;
	if (!lst)
		return (0);
	temp = lst;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

// temp function
void	print_lst(t_node *lst)
{
	t_node	*temp;

	temp = lst;
	while (temp)
	{
		printf("%d ", temp->nbr);
		temp = temp->next;
	}
	printf("\n");
}
