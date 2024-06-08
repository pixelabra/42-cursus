/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:24:24 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 20:34:13 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_movement(int keycode, t_mlx_data *data)
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
	if (keycode == KEY_P)
		data->config->projection = PARALLEL;
	if (keycode == KEY_I)
		data->config->projection = ISOMETRIC;
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
}

void	handle_features(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
	{
		free_data(data);
		exit(0);
	}
	else if (keycode == KEY_PLUS)
		data->config->zoom += 2;
	else if (keycode == KEY_MINUS)
		data->config->zoom -= 2;
	else if (keycode == KEY_Z)
		data->config->inc_z += 2;
	else if (keycode == KEY_X)
		data->config->inc_z -= 2;
	else if (keycode == KEY_R)
		reset(data->config, data->init_config);
	else
	{
		handle_movement(keycode, data);
		handle_projection(keycode, data);
		handle_rotation(keycode, data);
	}
}

int	deal_key(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_R_PLUS)
		adj_colours(data, R, 10);
	else if (keycode == KEY_R_MINUS)
		adj_colours(data, R, -10);
	else if (keycode == KEY_G_PLUS)
		adj_colours(data, G, 10);
	else if (keycode == KEY_G_MINUS)
		adj_colours(data, G, -10);
	else if (keycode == KEY_B_PLUS)
		adj_colours(data, B, 10);
	else if (keycode == KEY_B_MINUS)
		adj_colours(data, B, -10);
	handle_features(keycode, data);
	draw(data);
	return (0);
}
