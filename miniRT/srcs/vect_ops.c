/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:19:45 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/21 14:50:47 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

inline t_vect	add_point_and_vector(t_vect *point, t_vect *vector)
{
	t_vect	result;

	if (!point || !vector)
		return (error_vect());
	result.x = point->x + vector->x;
	result.y = point->y + vector->y;
	result.z = point->z + vector->z;
	result.w = 1;
	return (result);
}

inline t_vect	subtract_point_and_vector(t_vect *point, t_vect *vector)
{
	t_vect	result;

	if (!point || !vector)
		return (error_vect());
	result.x = point->x - vector->x;
	result.y = point->y - vector->y;
	result.z = point->z - vector->z;
	result.w = 1;
	return (result);
}

inline t_vect	add_vectors(t_vect *v1, t_vect *v2)
{
	t_vect	result;

	if (!v1 || !v2)
		return (error_vect());
	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	result.w = 0;
	return (result);
}

inline t_vect	subtract_vectors(t_vect *v1, t_vect *v2)
{
	t_vect	result;

	if (!v1 || !v2)
		return (error_vect());
	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	result.w = 0;
	return (result);
}

inline t_vect	multiply_vect(t_vect *vect, float multiplier)
{
	t_vect	result;

	if (!vect)
		return (error_vect());
	result.x = vect->x * multiplier;
	result.y = vect->y * multiplier;
	result.z = vect->z * multiplier;
	result.w = vect->w;
	return (result);
}

inline t_vect	divide_vect(t_vect *vect, float divisor)
{
	t_vect	result;

	if (!vect)
		return (error_vect());
	result.x = vect->x / divisor;
	result.y = vect->y / divisor;
	result.z = vect->z / divisor;
	result.w = vect->w;
	return (result);
}
