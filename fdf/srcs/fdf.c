/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/18 02:39:53 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int	i;
		int	j;
		mlx_data *matrix;
		matrix = malloc(sizeof(mlx_data));
		build_matrix(matrix, argv);

		i = 0;
		while (i < matrix->width)
		{
			j = 0;
			while (j < matrix->length)
			{
				printf("%3d", matrix->matrix[i][j]);
				j++;
			}
			i++;
		}

	}
	return (0);
}
