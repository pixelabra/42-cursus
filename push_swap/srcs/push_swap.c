/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:26:34 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/17 16:26:34 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;

	a = NULL;
	b = NULL;
	if (ac < 2 || (ac == 2 && !(*av[1])))
		ps_error(NULL, NULL, NULL);
	ps_stack_init(ac, av, &a);
	if (!issorted(&a))
	{
		if (ps_lstsize(a) == 2)
		{
			swap(&a);
			ft_putendl_fd("sa", 1);
		}
		else if (ps_lstsize(a) == 3)
			sort_three(&a);
		else
			push_push(&a, &b);
	}
	ps_lstclear(&a);
	ps_lstclear(&b);
	return (0);
}
