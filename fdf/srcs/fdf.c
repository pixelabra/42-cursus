/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/01 02:50:43 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	deal_key(int key, t_mlx_data *matrix)
{
	if (key == 65307) // or 65307 for X11/Linux
	{
		mlx_destroy_window(matrix->mlx_ptr, matrix->win_ptr);
		exit(0);
	}
	if (key == 65362) //up
		matrix->shift_x -= 10;
	if (key == 65363) //right
		matrix->shift_y += 10;
	if (key == 65364) //down
		matrix->shift_x += 10;
	if (key == 65361) //left
		matrix->shift_y -= 10;
	mlx_clear_window(matrix->mlx_ptr, matrix->win_ptr);
	// draw(matrix);
	printf("%d\n", key);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_mlx_data *data;
		data = malloc(sizeof(t_mlx_data));
		build_matrix(data, argv);
		data->mlx_ptr = mlx_init();
		data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
		data->img.width = WIN_WIDTH;
		data->img.height = WIN_HEIGHT;
		create_image(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
		// data->zoom = 20;
		// draw(matrix);
		mlx_key_hook(data->win_ptr, deal_key, data);
		mlx_loop(data->mlx_ptr);
	}
	return (0);
}
