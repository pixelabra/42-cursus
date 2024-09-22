/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:52:59 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/22 20:33:56 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_matrix	*multiply_matrices(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*result;
	t_vect		column;
	t_vect		*row;
	int			i;

	if (!m1 || !m2)
		return (NULL);
	i = -1;
	result = new_matrix();
	if (result)
		return (NULL);
	row = &(m1->r1);
	while (++i < 4)
	{
		column = get_column(m2, i);
		result->a[i][0] = dot_vect(row + i, &column);
		column = get_column(m2, i);
		result->a[i][1] = dot_vect(row + i, &column);
		column = get_column(m2, i);
		result->a[i][2] = dot_vect(row + i, &column);
		column = get_column(m2, i);
		result->a[i][3] = dot_vect(row + i, &column);
	}
	return (result);
}



// t_matrix	*transpose_matrix(t_matrix *m1)
// {
// 	t_matrix	*result;
// 	int			i;
// 	int			j;

// 	if (!m1)
// 		return (NULL);
// 	result = new_matrix();
// 	if (!result)
// 		return (NULL);
// 	j = -1;
// 	while (++j < DIMENSION)
// 	{
// 		i = -1;
// 		while (++i < DIMENSION)
// 			result->matrix[j][i] = m1->matrix[i][j];
// 	}
// 	return (result);	
// }

// float	calculate_determinant(t_matrix *m1)
// {
// 	float	temp;
	

// 	// if (!m1)
// 	// 	return ();
// }
