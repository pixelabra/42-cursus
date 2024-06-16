/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:39:02 by agodeanu          #+#    #+#             */
/*   Updated: 2024/06/16 21:24:03 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H

# define CHECKER_H

# include "push_swap.h"

int		moves(t_node **a, t_node **b, char *line);
int		moves_cntnd(t_node **a, t_node **b, char *line);
void	apply_moves(t_node **a, t_node **b, char *line);

#endif