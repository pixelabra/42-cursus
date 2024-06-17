/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 01:55:45 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/17 13:37:34 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_dblptr(char **dblptr)
{
	int	i;

	i = 0;
	while (dblptr[i])
		free(dblptr[i++]);
	free(dblptr);
}

void	ps_error(char *ptr, char **dblptr)
{
	if (ptr)
		free(ptr);
	if (dblptr)
		free_dblptr(dblptr);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	ps_lstclear(t_node **lst)
{
	t_node	*temp;
	t_node	*next;

	if (!lst || !(*lst))
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

void	ps_error_lst(t_node **a, t_node **b)
{
	if (a && *a)
		ps_lstclear(a);
	if (b && *b)
		ps_lstclear(b);
	ps_error(NULL, NULL);
}
