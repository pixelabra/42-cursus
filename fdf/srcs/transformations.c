/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:35:07 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/08 00:39:11 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	transform_points(t_mlx_data *data, t_coord **temp_matrix)
{
	int	i;
	int	j;

	j = -1;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			if (data->config->apply_roty)
				rotation_y(&temp_matrix[j][i], data->config);
			zoomer(&temp_matrix[j][i], data->config);	
			isometric(&temp_matrix[j][i], data->config);
		}
	}
	data->config->apply_roty = 0;
}

int	max_z(t_mlx_data *data)
{
	int	i;
	int	j;
	int	max_z;
	int	current_z;

	j = -1;
	max_z = 1;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			current_z = br_abs(data->matrix[j][i].z);
			if (current_z > max_z)
				max_z = current_z;
		}
	}
	return (max_z);
}

void	zoomer(t_coord *coord, t_mlx_camera *config)
{
	coord->x *= config->zoom;
	coord->y *= config->zoom;
}

void	rotation_x(t_coord *coord, t_mlx_camera *config)
{
	int	initial_y;
	int	initial_z;

	initial_y = coord->y;
	initial_z = coord->z;
	coord->y = initial_y * cos(config->angle_x) - initial_z * sin(config->angle_x);
	coord->z = -initial_y * sin(config->angle_x) + initial_z * cos(config->angle_x);
}

void	rotation_y(t_coord *coord, t_mlx_camera *config)
{
	int	initial_x;
	int	initial_z;

	initial_x = coord->x;
	initial_z = coord->z;
	coord->x = initial_x * cos(config->angle_y) + initial_z * sin(config->angle_y);
	coord->z = -initial_x * sin(config->angle_y) + initial_z * cos(config->angle_y);
}

void	rotation_z(t_coord *coord, t_mlx_camera *config)
{
	int	initial_x;
	int	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = initial_x * cos(config->angle_z) - initial_y * sin(config->angle_z);
	coord->y = initial_x * sin(config->angle_z) + initial_y * cos(config->angle_z);
}

void	isometric(t_coord *coord, t_mlx_camera *config)
{
	int	initial_x;
	int	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = config->shift_x + (initial_x - initial_y) * cos(3.14 / 6);
	coord->y = config->shift_y + (initial_x + initial_y) * sin(3.14 / 6 ) - coord->z;
}
