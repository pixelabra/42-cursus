/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/25 02:01:59 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	deal_key(int key, void *data)
{
	mlx_data *matrix;

	matrix = (mlx_data *)data;
	if (key == 53 || key == 65307) // or 65307 for X11/Linux
	{
		mlx_destroy_window(matrix->connection, matrix->win);
		exit(0);
	}
	printf("%d", key);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		mlx_data *matrix;
		matrix = malloc(sizeof(mlx_data));
		build_matrix(matrix, argv);
		matrix->connection = mlx_init();
		matrix->win = mlx_new_window(matrix->connection, 1000, 1000, "FDF");
		matrix->zoom = 20;
		draw(matrix);
		mlx_key_hook(matrix->win, deal_key, matrix);
		mlx_loop(matrix->connection);
	}
	return (0);
}
