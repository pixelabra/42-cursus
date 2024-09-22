/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:50:45 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/22 19:31:7 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_matrix	*new_matrix(void)
{
	t_matrix	*temp;

	temp = ft_calloc(1, sizeof(t_matrix));
	if (!temp)
		return (NULL);
	return (temp);
}

int	compare_matrices(t_matrix *m1, t_matrix *m2)
{
	if (!m1 || !m2)
		return (-1);
	if (compare_vects(&m1->r1, &m2->r1) || compare_vects(&m1->r2, &m2->r2)
		|| compare_vects(&m1->r3,  &m2->r3) || compare_vects(&m1->r4, &m2->r4))
		return (1);
	return (0);
}

t_matrix	*add_matrices(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*result;

	if (!m1 || !m2)
		return (NULL);
	result = new_matrix();
	if (!result)
		return (NULL);
	result->r1 = add_vectors(&m1->r1, &m2->r1);
	result->r2 = add_vectors(&m1->r2, &m2->r2);
	result->r3 = add_vectors(&m1->r3, &m2->r3);
	result->r4 = add_vectors(&m1->r4, &m2->r4);
	return (result);
}

t_matrix	*subtract_matrices(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*result;

	if (!m1 || !m2)
		return (NULL);
	result = new_matrix();
	if (!result)
		return (NULL);
	result->r1 = subtract_vectors(&m1->r1, &m2->r1);
	result->r2 = subtract_vectors(&m1->r2, &m2->r2);
	result->r3 = subtract_vectors(&m1->r3, &m2->r3);
	result->r4 = subtract_vectors(&m1->r4, &m2->r4);
	return (result);
}

t_matrix	*multiply_matrix(t_matrix *m1, float nbr)
{
	t_matrix	*result;

	if (!m1)
		return (NULL);
	result = new_matrix();
	if (!result)
		return (NULL);
	result->r1 = multiply_vect(&m1->r1, nbr);
	result->r2 = multiply_vect(&m1->r2, nbr);
	result->r3 = multiply_vect(&m1->r3, nbr);
	result->r4 = multiply_vect(&m1->r4, nbr);
	return (result);
}

t_vect	get_column(t_matrix *m, int index)
{
	t_vect	result;

	if (!m || index < 0 || index > 3)
		return (error_vect());
	result.a[0] = m->[0][i];
	result.a[1] = m->[1][i];
	result.a[2] = m->[2][i];
	result.a[3] = m->[3][i];
	return (result);
}
