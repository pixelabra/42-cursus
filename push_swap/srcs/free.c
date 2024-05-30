/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 01:55:45 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/30 22:28:52 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_dblptr(char **dblptr)
{
	int	i;

	i = -1;
	while (dblptr[++i])
		free(dblptr[i]);
	free(dblptr);
}

void	ps_error(char *ptr, char **dblptr)
{
	if (ptr)
		free(ptr);
	if (dblptr)
		free_dblptr(dblptr);
	ft_putendl_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}
