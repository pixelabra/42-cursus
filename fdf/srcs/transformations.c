/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:35:07 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/05 22:35:29 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	transform_points(t_mlx_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			zoomer(&data->matrix[j][i], data);	
			isometric(&data->matrix[j][i], data->config);
		}
	}
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

void	zoomer(t_coord *coord, t_mlx_data *data)
{
	int	zoom_factor;
	(void) data;
	// zoom_factor = 1000 / max_z(data);
	zoom_factor = 20;
	coord->x *= zoom_factor;
	coord->y *= zoom_factor;
}

void	isometric(t_coord *coord, t_mlx_camera *config)
{
	int	initial_x;
	int	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = config->shift_x + (initial_x - initial_y) * cos(3.14 / 6);
	coord->y = config->shift_y + (initial_x + initial_y) * sin(3.14 / 6 ) - 25 * coord->z;
}
