/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/07 02:47:07 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_null(t_mlx_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->matrix = NULL;
	data->config = NULL;
	data->init_config = NULL;
	data->img.img_ptr = NULL;
	data->img.addr = NULL;
}

t_mlx_data	*init_mlx_data(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (!data)
		exit(0);
	init_null(data);
	data->config = malloc(sizeof(t_mlx_camera));
	if (!data->config)
		free_init(data);
	data->init_config = malloc(sizeof(t_mlx_camera));
	if (!data->init_config)
		free_init(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		free_init(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!data->win_ptr)
		free_init(data);
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
	init_config(data->config, data->init_config);
	return (data);
}

void	init_config(t_mlx_camera *config, t_mlx_camera *init_config)
{
	config->shift_x = 300;
	config->shift_y = 400;
	config->inc_z = 0;
	config->zoom = 10;
	config->angle_x = 0;
	config->angle_y = 0;
	config->angle_z = 0;
	config->projection = ISOMETRIC;
	init_config->shift_x = 300;
	init_config->shift_y = 400;
	init_config->inc_z = 0;
	init_config->zoom = 10;
	init_config->angle_x = 0;
	init_config->angle_y = 0;
	init_config->angle_z = 0;
	init_config->projection = ISOMETRIC;
}

void	reset(t_mlx_camera *config, t_mlx_camera *init_config)
{
	config->shift_x = init_config->shift_x;
	config->shift_y = init_config->shift_y;
	config->inc_z = init_config->inc_z;
	config->zoom = init_config->zoom;
	config->angle_x = init_config->angle_x;
	config->angle_y = init_config->angle_y;
	config->angle_z = init_config->angle_z;
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
		ft_error(5, NULL, -1);
	file_checker(argv);
	data = init_mlx_data();
	build_matrix(data, argv);
	draw(data);
	mlx_hook(data->win_ptr, 2, 1L>>0, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
