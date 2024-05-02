/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/03 00:57:37 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// void isometric(float *x, float *y, int z)
// {
//     float original_x = *x;
//     float original_y = *y;
//     *x = (original_x - original_y) * cos(-10);
//     *y = (original_x + original_y) * sin(-10) - z;
// }

// int calculate_colour(int i, int j, int width, int height) //remove/change
// {
//     int centerX = width / 2;
//     int centerY = height / 2;
//     double max_distance = sqrt(centerX * centerX + centerY * centerY);
//     double distance = sqrt((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY));
//     int brightness = 255 - (int)(255 * (distance / max_distance));
//     brightness = MAX(0, MIN(brightness, 255)); // Ensure within bounds
//     return (brightness << 16) | (brightness << 8) | brightness; // RGB grayscale
// }

void	create_image(t_mlx_data *data)
{
	int		i;
	int		j;
	int 	colour;
	char	*pixel_addr;

	colour = 0x000000;
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	j = -1;
	while (++j < data->img.height)
	{
		i = -1;
		while (++i < data->img.width)
		{
			// colour = calculate_colour(i, j, data->img.width, data->img.height);
			pixel_addr = data->img.addr + (j * data->img.line_length + i * (data->img.bits_per_pixel / 8));
			if (data->img.endian == 0)	
                *(unsigned int*)pixel_addr = mlx_get_color_value(data->mlx_ptr, colour);
		}
	}
}

unsigned int	colour(t_coord start, t_coord end)
{
	(void) start;
	(void) end;
	return (0xFF0000);
}

void	draw_pixel_to_image(t_mlx_data *data, t_coord start, unsigned int colour)
{
	char	*pixel_addr;

	if (start.x < 0 || start.x >= data->img.width 
		|| start.y < 0 || start.y >= data->img.height)
			return ;
	pixel_addr = data->img.addr + (start.y * data->img.line_length + start.x * (data->img.bits_per_pixel / 8));
	*(unsigned int *) pixel_addr = mlx_get_color_value(data->mlx_ptr, colour); 
	
}

int	bresenham_step(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

int	br_abs(int number)
{
	if (number < 0)
		number *= -1;
	return (number);
}

t_br_param	bresenham_setup(t_coord start, t_coord end)
{
	t_br_param	params;

	params.abs_dx = br_abs(end.x - start.x);
	params.abs_dy = -br_abs(end.y - start.y);
	params.x_step = bresenham_step(start.x, end.x);
	params.y_step = bresenham_step(start.y, end.y);
	params.decision = params.abs_dx + params.abs_dy;
	return (params);
}

void bresenham_algo(t_mlx_data *data, t_coord start, t_coord end)
{
	t_br_param	params;
    int 		decision2x;

	params = bresenham_setup(start, end);
    while (1)
	{
        draw_pixel_to_image(data, start, colour(start, end));
        if (start.x == end.x && start.y == end.y)
			break ;
		decision2x = 2 * params.decision;
        if (decision2x >= params.abs_dy)
		{
			params.decision += params.abs_dy;
			start.x += params.x_step;
        }
        if (decision2x < params.abs_dx)
		{
			params.decision += params.abs_dx;
			start.y += params.y_step;
        }
    }
}

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
			zoomer(&data->matrix[j][i]);
			isometric(&data->matrix[j][i]);
		}
	}
}

void	zoomer(t_coord *coord)
{
	coord->x *= 10;
	coord->y *= 10;
}

void	isometric(t_coord *coord)
{
	int	initial_x;
	int	initial_y;

	initial_x = coord->x;
	initial_y = coord->y;
	coord->x = 400 + (initial_x - initial_y) * cos(3.14 / 6);
	coord->y = 200 + (initial_x + initial_y) * sin(3.14 / 6 ) - 25 * coord->z;
}

void	draw(t_mlx_data *data)
{
	int	i;
	int	j;

	j = -1;
	transform_points(data);
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			if (i < data->width - 1)
				bresenham_algo(data, data->matrix[j][i], data->matrix[j][i + 1]);
			if (j < data->height - 1)
				bresenham_algo(data, data->matrix[j][i], data->matrix[j + 1][i]);
		}
	}
}
