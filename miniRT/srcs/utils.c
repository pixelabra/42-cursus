/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:46:33 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/22 00:59:30 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Function to obtain the square of a number
float	sqr(float nbr)
{
	return (nbr * nbr);
}

// Obtains the length squared of a vector
float	vect_lengthsq(t_vect *vect)
{
	if (!vect)
		return (0);
	return (sqr(vect->x) + sqr(vect->y) + sqr(vect->z));
}

// Obtains the length of a vector
float	vect_length(t_vect *vect)
{
	return (sqrt(vect_lengthsq(vect)));
}

// Function to avoid float point comparison inaccuracy
inline int	compare_float(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return (0);
	return (1);
}
