/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:46:33 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/22 19:19:12 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Function to obtain the square of a number
inline float	sqr(float nbr)
{
	return (nbr * nbr);
}

// Obtains the length squared of a vector
inline float	vect_lengthsq(t_vect *vect)
{
	if (!vect)
		return (0);
	return (sqr(vect->x) + sqr(vect->y) + sqr(vect->z));
}

// Obtains the length of a vector
inline float	vect_length(t_vect *vect)
{
	return (sqrtf(vect_lengthsq(vect)));
}

// Function to avoid float point comparison inaccuracy
inline int	compare_float(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return (0);
	return (1);
}

// Free double float array
inline void	free_dblptr(void **dblptr)
{
	int	i;

	if (!dblptr)
		return ;
	i = 0;
	while (dblptr[i])
		free(dblptr[i++]);
	free(dblptr);
}
