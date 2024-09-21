/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:59:17 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/21 18:06:03 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vect	error_vect(void)
{
	t_vect	vect;

	vect.x = 0;
	vect.y = 0;
	vect.z = 0;
	vect.w = -1;
	return (vect);
}

void	print_vect(t_vect vect, char *name)
{
	if (name)
		printf(MAGENTA"%s: ", name);
	printf(BOLD RED"X:%f "YELLOW"Y:%f "GREEN"Z:%f ",
		vect.x, vect.y, vect.z);
	if (vect.w == 0)
		printf(BLUE"VECTOR\n"RESET);
	else if (vect.w == 1)
		printf(CYAN"POINT\n"RESET);
}


// Create and return a stack allocated vector
t_vect	create_vect(float x, float y, float z, int w)
{
	t_vect	new_temp;

	new_temp.x = x;
	new_temp.y = y;
	new_temp.z = z;
	new_temp.w = w;
	return (new_temp);
}

// Create and return a heap allocated vector
t_vect	*new_vect(float x, float y, float z, int w)
{
	t_vect	*new_temp;

	new_temp = ft_calloc(1, sizeof(t_vect));
	if (!new_temp)
		return (NULL);
	new_temp->x = x;
	new_temp->y = y;
	new_temp->z = z;
	new_temp->w = w;
	return (new_temp);
}

// Modify vect objects
t_vect	normalise_vect(t_vect *vect)
{
	float	length;
	t_vect	result;

	length = vect_length(vect);
	if (!length)
		return (error_vect());
	result.x = vect->x / length;
	result.y = vect->y / length;
	result.z = vect->z / length;
	return (result);
}		
