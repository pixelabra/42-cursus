/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:28:51 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:29:16 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	br_step(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

int	br_abs(int number)
{
	if (number < 0)
		number *= -1;
	return (number);
}

int	br_max(int abs_dx, int abs_dy)
{
	if (abs_dx >= abs_dy)
		return ((int) abs_dx);
	return ((int) abs_dy);
}
