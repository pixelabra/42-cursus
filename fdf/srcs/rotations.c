/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:37:28 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:37:59 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotation_x(t_coord *coord, t_mlx_camera *config)
{
	float	initial_y;
	float	initial_z;

	initial_y = coord->y;
	initial_z = coord->z;
	coord->y = initial_y * cos(config->angle_x)
		+ initial_z * sin(config->angle_x);
	coord->z = -initial_y * sin(config->angle_x)
		+ initial_z * cos(config->angle_x);
}

void	rotation_y(t_coord *coord, t_mlx_camera *config)
{
	float	initial_x;
	float	initial_z;

	initial_x = coord->x;
	initial_z = coord->z;
	coord->x = initial_x * cos(config->angle_y)
		+ initial_z * sin(config->angle_y);
	coord->z = -initial_x * sin(config->angle_y)
		+ initial_z * cos(config->angle_y);
}

void	rotation_z(t_coord *coord, t_mlx_camera *config)
{
	float	initial_x;
	float	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = initial_x * cos(config->angle_z)
		- initial_y * sin(config->angle_z);
	coord->y = initial_x * sin(config->angle_z)
		+ initial_y * cos(config->angle_z);
}
