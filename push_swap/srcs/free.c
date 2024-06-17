/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:25:50 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:25:50 by agodeanu         ###   ########.fr       */
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

void	ps_error(char *ptr, char **dblptr, t_node **a)
{
	if (ptr)
		free(ptr);
	if (dblptr)
		free_dblptr(dblptr);
	if (a && *a)
		ps_lstclear(a);
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
	ps_error(NULL, NULL, NULL);
}

void	isemptyargs(int ac, char **av)
{
	int	i;
	int	j;

	if (!av)
		ps_error(NULL, NULL, NULL);
	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (!av[i][j])
			ps_error(NULL, NULL, NULL);
		while (av[i][j])
		{
			if (av[i][j] != ' ')
				break ;
			if (j == (int)ft_strlen(av[i]) - 1)
				ps_error(NULL, NULL, NULL);
			j++;
		}
	}
}
