/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:14:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/06 02:04:46 by a3y3g1           ###   ########.fr       */
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
		ps_error(NULL, NULL);
	ps_stack_init(ac, av, &a);
	if (ps_lstsize(a) == 3)
		sort_three(&a);
	else
		push_push(&a, &b);
	ps_lstclear(&a);
	ps_lstclear(&b);
	return (0);
}
