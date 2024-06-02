/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:14:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/02 22:30:02 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;
	
	t_node	*temp;

	a = NULL;
	b = NULL;
	(void) b;
	if (ac < 2 || (ac == 2 && !(*av[1])))
		ps_error(NULL, NULL);
	ps_stack_init(ac, av, &a);
	print_lst(a);
	
	temp = next_big(&a, -2147483648);
	printf("%d\n", temp->nbr);
	
	ps_lstclear(&a);
	return (0);
}
