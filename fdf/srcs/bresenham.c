/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:36:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/25 22:18:02 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	bresenham_step(float start, float end)
{
	if (start < end)
		return (1);
	return (-1);
}

float	br_abs(int number)
{
	if (number < 0)
		number *= -1;
	return (number);
}

void	draw_pixel_to_image(t_mlx_data *data, t_coord start, unsigned int colour)
{
	char	*pixel_addr;

	if (start.x < 0 || start.x >= data->img.width 
		|| start.y < 0 || start.y >= data->img.height)
			return ;
	pixel_addr = data->img.addr + ((int) start.y * data->img.line_length + (int) start.x * (data->img.bits_per_pixel / 8));
	*(unsigned int *) pixel_addr = mlx_get_color_value(data->mlx_ptr, colour); 
	
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
        if (br_abs(start.x - end.x) <= 1 && br_abs(start.y - end.y) <= 1)
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