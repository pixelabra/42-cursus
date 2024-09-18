/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 01:24:40 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/17 01:55:25 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// Initial structure of vector
typedef struct s_Vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

// Function to obtain the square of a number
double	sqr(double nbr)
{
	return (nbr * nbr);
}

// Obtains the length squared of a vector
double	v_lengthsq(t_vect vect)
{
	return (sqr(vect.x) + sqr(vect.y) + sqr(vect.z));
}

// Obtains the length of a vector
double	v_length(t_vect vect)
{
	return (sqrt(v_lengthsq(vect)));
}

// Normalises the vector which  means it divides each component by the length
double	v_normalise(t_vect *vect)
{
	double	length;

	length = v_length(*vect);
	if (!length)
		return (0);
	vect->x /= length;
	vect->y /= length;
	vect->z /= length;
	return (length);
}

// This returns a normalised copy of the vector
t_vect	v_normalised(t_vect vect)
{
	v_normalise(&vect);
	return (vect);
}

// Modifies vector by multiplying it w/ a nbr
void	v_multiply(t_vect *vect, double nbr)
{
	if (!vect)
		return (NULL);
	vect->x = vect->x * nbr;
	vect->y = vect->y * nbr;
	vect->z = vect->z * nbr;
}

// Returns a new vector that is the addition of those two
inline t_vect	v_addition(t_vect v1, t_vect v2)
{
	t_vect	add_temp;

	add_temp.x = v1.x + v2.x;
	add_temp.y = v1.y + v2.y;
	add_temp.z = v1.z + v2.z;
	return (add_temp);
}

// Returns a new Multiplication
inline t_vect	v_mult(t_vect  v1, double nbr)
{
	t_vect	mult_temp;

	mult_temp.x *= nbr;
	mult_temp.y *= nbr;
	mult_temp.z *= nbr;
	return (mult_temp);
}

// Returns a copy vector
t_vect	*v_copy(t_vect v1)
{
	t_vect	*copy_temp;

	copy_temp = malloc(sizeof(t_vect));
	if (!copy_temp)
		return (NULL);
	copy_temp->x = v1.x;
	copy_temp->y = v1.y;
	copy_temp->z = v1.z;
	return (copy_temp);
}

// Returns the dot product of two vectors
inline double	v_dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Returns the cross product of two vectors
inline t_vect	v_cross(t_vect v1, t_vect v2)
{
	t_vect	cross_temp;

	cross_temp.x = v1.y * v2.z - v1.z * v2.y;
	cross_temp.y = v1.z * v2.x - v1.x * v2.z;
	cross_temp.z = v1.x * v2.y - v2.y * v2.x;
	return (cross_temp);
}

// Create a new vector w/ the coordinates
t_vect	*v_new(double x, double y, double z)
{
	t_vect	*new_temp;

	new_temp = malloc(sizeof(t_vect));
	if (!new_temp)
		return (NULL);
	new_temp->x = x;
	new_temp->y = y;
	new_temp->z = z;
}

int	main(void)
{

	return (0);
}
