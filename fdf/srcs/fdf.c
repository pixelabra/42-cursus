/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/05 23:07:02 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	deal_key(int keycode, t_mlx_data *data)
{	
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_data(data);
		exit(0);
	}
    if (keycode == 65362)
        data->config->shift_x -= 10;
	else if (keycode == 65363)
        data->config->shift_y += 10;
	else if (keycode == 65364)
		data->config->shift_x += 10;
	else if (keycode == 65361) // Left arrow
        data->config->shift_y -= 10;
	else
		printf("NOTHING");
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	create_image(data);
	draw(data);
	printf("Key event: %d\n", keycode);
	return (0);
}

t_mlx_data	*init_mlx_data()
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (!data)
		exit(0);
	data->config = malloc(sizeof(t_mlx_camera));
	if (!data->config) //free data
		exit(0);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
	data->config->shift_x = 300;
	data->config->shift_y = 400;
	data->config->max_z = 1;
	data->config->zoom = 1;
	return (data);
}

int	close_window(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_mlx_data 		*data;

	if (argc != 2)
		return (1);
	data = init_mlx_data();
	build_matrix(data, argv);
	draw(data);
	// mlx_key_hook(data->win_ptr, deal_key, data);
	
	mlx_hook(data->win_ptr, 2, 1L>>0, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
