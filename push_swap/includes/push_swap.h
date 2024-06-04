/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:18:03 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/03 16:16:47 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H

# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

typedef enum s_flag
{
	RotRot,
	RotRev,
	RevRot,
	RevRev
}	t_flag;

typedef struct s_node
{
	int				nbr;
	int				index;
	int				cost;
	t_flag			flag;
	struct s_node	*target;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// parsing & init
void	ps_stack_init(int ac, char **av, t_node **a);
char	*ps_join_arg(int ac, char **av);

// error handling
void	ps_error(char *ptr, char **dblptr);
void	isvalidnbr(char *sep_arg, char **sep_args);
long	ps_atol(char *sep_arg, char **sep_args);
void	isduplicate(t_node *lst);

// free stuff
void	free_dblptr(char **dblptr);
void	ps_lstclear(t_node **lst);
void	ps_error_lst(t_node **a, t_node **b);

// lst utils
t_node	*ps_lstnew(int nbr, int i);
t_node *ps_lstlast(t_node *lst);
void	ps_lstadd_back(t_node **lst, t_node *new);
void	ps_lstadd_front(t_node **lst, t_node *new);
int		ps_lstsize(t_node *lst);
void	print_lst(t_node *lst);
void	refresh_index(t_node **stack);

// push arithmetics
void	swap(t_node **a);
t_node	*pop(t_node **stack);
void	push(t_node **pushee, t_node **pusher);
void	rotate(t_node **stack);
void	reverse(t_node **stack);
int		max_nbr(int nbr1, int nbr2);

// operations
t_node	*abs_min(t_node **stack);
t_node	*abs_max(t_node **stack);
t_node	*next_small(t_node **stack, int nbr);
t_node	*next_big(t_node **stack, int nbr);

// algo utils
void	set_target_cost(t_node **stack1, t_node **stack2);
void	set_cost(t_node *stack, int size1, int size2);
void	algo_moves(t_node **stack1, t_node **stack2);
void	first_push(t_node **stack1, t_node **stack2);

// moves
void	rot_rot(t_node *node, t_node **stack1, t_node **stack2);
void	rev_rev(t_node *node, t_node **stack1, t_node **stack2);
void	rot_rev(t_node *node, t_node **stack1, t_node **stack2, int size2);
void	rev_rot(t_node *node, t_node **stack1, t_node **stack2, int size1);

#endif