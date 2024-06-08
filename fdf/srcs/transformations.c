/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:35:07 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:37:52 by a3y3g1           ###   ########.fr       */
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
			zoomer(&temp_matrix[j][i], data->config);
			rotation_x(&temp_matrix[j][i], data->config);
			rotation_y(&temp_matrix[j][i], data->config);
			rotation_z(&temp_matrix[j][i], data->config);
			if (data->config->projection == ISOMETRIC)
				isometric(&temp_matrix[j][i], data->config);
			else if (data->config->projection == PARALLEL)
				parallel(&temp_matrix[j][i], data->config);
		}
	}
}

void	zoomer(t_coord *coord, t_mlx_camera *config)
{
	coord->x *= config->zoom;
	coord->y *= config->zoom;
	coord->z *= config->zoom + config->inc_z;
}

void	isometric(t_coord *coord, t_mlx_camera *config)
{
	float	initial_x;
	float	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = config->shift_x
		+ (initial_x - initial_y) * cos(3.14159 / 6);
	coord->y = config->shift_y
		+ (initial_x + initial_y) * sin(3.14159 / 6) - coord->z;
}

void	parallel(t_coord *coord, t_mlx_camera *config)
{
	coord->x = config->shift_x + coord->x;
	coord->y = config->shift_y + coord->y - coord->z;
}
