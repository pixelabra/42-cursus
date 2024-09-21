/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:43:18 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/22 00:20:53 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_rgb	get_rgb(unsigned int colour)
{
	t_rgb	rgb;

	rgb.a = ((colour >> 24) & 0xFF);
	rgb.r = ((colour >> 16) & 0xFF);
	rgb.g = ((colour >> 8) & 0xFF);
	rgb.b = ((colour >> 0) & 0xFF);
	return (rgb);
}

unsigned int	interpolate_colour(t_rgb start_rgb, t_rgb end_rgb, float t)
{
	t_rgb			rgb;
	unsigned int	colour;

	rgb.r = (unsigned char)(start_rgb.r + t * (end_rgb.r - start_rgb.r));
	rgb.g = (unsigned char)(start_rgb.g + t * (end_rgb.g - start_rgb.g));
	rgb.b = (unsigned char)(start_rgb.b + t * (end_rgb.b - start_rgb.b));
	rgb.a = (unsigned char)(start_rgb.a + t * (end_rgb.a - start_rgb.a));
	colour = (rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | (rgb.b << 0);
	return (colour);
}

void	drawpximg(t_data *data, int i, int j, float t)
{
	char	*pixel_addr;

	pixel_addr = data->img.addr + (j * data->img.line_length
		+ i * (data->img.bits_per_pixel / 8));
	* (unsigned int *) pixel_addr = mlx_get_color_value
		(data->mlx_ptr, interpolate_colour(get_rgb(0x0000FF00), get_rgb(0x00FF0000), t));
}

void	draw(t_data *data)
{
	int			i;
	int			j;
	float		t;
	t_vect		p1;
	t_vect		p2;

	p1 = create_vect(0, 0, 0, 1);
	p2 = create_vect(1600, 900, 0, 1);
	j = (int)p1.y;
	create_image(data);
	while (j < (int)p2.y)
	{
		i = (int)p1.x;
		t = 0;
		while (i < (int)p2.x)
		{
			t += 1 / (p2.x - p1.x);
			drawpximg(data, i, j, t);
			// printf("%f\n", t);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}
