/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:50:45 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/22 01:07:15 by agodeanu         ###   ########.fr       */
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
	int	i;
	int	j;

	if (!m1 || !m2)
		return (-1);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (compare_float(m1->matrix[j][i], m2->matrix[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

t_matrix	add_matrices(t_matrix *m1, t_matrix *m2)
{
	t_matrix	result;
	int			i;
	int			j;

	// if (!m1 || !m2)
	// 	return (-1);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			result.matrix[j][i] = m1->matrix[j][i] + m2->matrix[j][i];
			i++;
		}
		j++;
	}
	return (result);
}

t_matrix	subtract_matrices(t_matrix *m1, t_matrix *m2)
{
	t_matrix	result;
	int			i;
	int			j;

	// if (!m1 || !m2)
	// 	return (-1);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			result.matrix[j][i] = m1->matrix[j][i] - m2->matrix[j][i];
			i++;
		}
		j++;
	}
	return (result);
}

t_matrix	multiply_matrix(t_matrix *m1, float nbr)
{
	t_matrix	result;
	int			i;
	int			j;

	// if (!m1 || !m2)
	// 	return (-1);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			result.matrix[j][i] = m1->matrix[j][i] * nbr;
			i++;
		}
		j++;
	}
	return (result);
}
