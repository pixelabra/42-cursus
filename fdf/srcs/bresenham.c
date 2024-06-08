/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:36:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:25:45 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	drawpximg(t_mlx_data *data, t_coord start, unsigned int colour)
{
	char	*pixel_addr;

	if (start.x < 0 || start.x >= data->img.width
		|| start.y < 0 || start.y >= data->img.height)
		return ;
	pixel_addr = data->img.addr + ((int) start.y * data->img.line_length
			+ (int) start.x * (data->img.bits_per_pixel / 8));
	*(unsigned int *) pixel_addr = mlx_get_color_value(data->mlx_ptr, colour);
}

t_br_param	br_setup(t_coord start, t_coord end)
{
	t_br_param	params;

	params.abs_dx = br_abs(end.x - start.x);
	params.abs_dy = -br_abs(end.y - start.y);
	params.x_step = br_step(start.x, end.x);
	params.y_step = br_step(start.y, end.y);
	params.decision = params.abs_dx + params.abs_dy;
	params.curr_step = 0;
	params.total_steps = br_max(params.abs_dx, -params.abs_dy);
	if (params.total_steps == 0)
		params.total_steps = 1;
	return (params);
}

void	br_inc(t_coord *start, t_br_param *params, int decision2x)
{
	if (decision2x >= params->abs_dy)
	{
		params->decision += params->abs_dy;
		start->x += params->x_step;
	}
	if (decision2x < params->abs_dx)
	{
		params->decision += params->abs_dx;
		start->y += params->y_step;
	}
}

void	br_algo(t_mlx_data *data, t_coord start, t_coord end)
{
	float		t;
	t_rgb		start_rgb;
	t_rgb		end_rgb;
	t_br_param	params;
	int			decision2x;

	start_rgb = get_rgb(start.colour);
	end_rgb = get_rgb(end.colour);
	params = br_setup(start, end);
	while (1)
	{
		t = (float) params.curr_step / (float) params.total_steps;
		if (t > 1.0)
			t = 1.0;
		drawpximg(data, start, interpolate_colour(start_rgb, end_rgb, t));
		if (br_abs(start.x - end.x) <= 1 && br_abs(start.y - end.y) <= 1)
			break ;
		decision2x = 2 * params.decision;
		br_inc(&start, &params, decision2x);
		params.curr_step++;
	}
}
