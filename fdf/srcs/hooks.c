/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:24:24 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/09 00:51:44 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_movement(int	keycode, t_mlx_data *data)
{
	if (keycode == KEY_UP)
        data->config->shift_y -= 5;
	else if (keycode == KEY_RIGHT)
        data->config->shift_x += 5;
	else if (keycode == KEY_DOWN)
		data->config->shift_y += 5;
	else if (keycode == KEY_LEFT)
        data->config->shift_x -= 5;
}

void	handle_projection(int keycode, t_mlx_data *data)
{
	(void) keycode;
	(void) data;
}

void	handle_rotation(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_Q)
		data->config->angle_x += 0.03;
	else if (keycode == KEY_A)
		data->config->angle_x -= 0.03;
	else if (keycode == KEY_W)
		data->config->angle_y += 0.03;
	else if (keycode == KEY_S)
		data->config->angle_y -= 0.03;
	else if (keycode == KEY_E)
		data->config->angle_z += 0.03;
	else if (keycode == KEY_D)
		data->config->angle_z -= 0.03;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->config->apply_rotx = 1;
	else if (keycode == KEY_W || keycode == KEY_S)
		data->config->apply_roty = 1;
	else if (keycode == KEY_E || keycode == KEY_D)
		data->config->apply_rotz = 1;
}

void	handle_features(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		// free_data(data);
		exit(0);
	}
	else if (keycode == KEY_PLUS)
		data->config->zoom += 2;
	else if (keycode == KEY_MINUS)
		data->config->zoom -= 2;
	else
	{
		handle_movement(keycode, data);
		handle_projection(keycode, data);
		handle_rotation(keycode, data);
	}
}

int	deal_key(int keycode, t_mlx_data *data)
{
	printf("Key event: %d\n", keycode);
	handle_features(keycode, data);
	create_image(data);
	draw(data);
	return (0);
}
