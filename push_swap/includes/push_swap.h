/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:18:03 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/29 23:58:07 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H

# define PUSH_SWAP_H

# include "../libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				push_cost;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

void	ps_stack_init(int ac, char **av, t_node **a);
char	*ps_join_arg(int ac, char **av);

void	ps_error(void);

#endif