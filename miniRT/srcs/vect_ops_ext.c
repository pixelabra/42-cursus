/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:12:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/20 23:24:52 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Returns a copy vector
inline t_vect	*copy_vect(t_vect *vect)
{
	t_vect	*copy_temp;

	copy_temp = malloc(sizeof(t_vect));
	if (!copy_temp)
		return (NULL);
	copy_temp->x = vect->x;
	copy_temp->y = vect->y;
	copy_temp->z = vect->z;
	copy_temp->w = 1;
	return (copy_temp);
}

// Returns the dot product of two vectors
inline float	dot_vect(t_vect *v1, t_vect *v2)
{
	if (!v1 || !v2)
		return (0);
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

// Returns the cross product of two vectors
inline t_vect	cross_vect(t_vect *v1, t_vect *v2)
{
	t_vect	cross_temp;

	if (!v1 || !v2)
		return (error_vect());
	cross_temp.x = v1->y * v2->z - v1->z * v2->y;
	cross_temp.y = v1->z * v2->x - v1->x * v2->z;
	cross_temp.z = v1->x * v2->y - v2->y * v2->x;
	cross_temp.w = 1;
	return (cross_temp);
}
