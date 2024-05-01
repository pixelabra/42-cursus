/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/02 01:25:01 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define MOD(a) (a - 2*a*(a < 0))
#define BIN(a)

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

void	bresenham_algo(t_mlx_data *data, t_coord start, t_coord end)
{
	int	x_step;
	int	y_step;
	int	error;
	int	error2;

	x_step = (start.x < end.x) ? 1 : -1;
	y_step = (start.y < end.y) ? 1 : -1;
	error = MOD(end.x - start.x) - MOD(end.y - start.y);
	while (1)
	{
		draw_pixel_to_image(data, start, colour(start, end));
		if (start.x == end.x  && start.y == end.y)
			break ;
		error2 = 2 * error;
		if (error2 >= -MOD(end.y - start.y))
		{
			error += -MOD(end.y - start.y);
			start.x += x_step;
		}	
		if (error2 <= MOD(end.x - start.x))
		{
			error += MOD(end.x - start.x);
			start.y += y_step;
		}
	}
}

// void	bresenham(float x, float y, float x1, float y1, t_mlx_data *matrix)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		max;
// 	int		z;
// 	int		z1;

// 	z = matrix->matrix[(int) x][(int) y];
// 	z1 = matrix->matrix[(int) x1][(int) y1];

// 	x *= matrix->zoom;
// 	y *= matrix->zoom;
// 	z *= matrix->zoom / 2;
// 	y1 *= matrix->zoom;
// 	x1 *= matrix->zoom;
// 	z1 *= matrix->zoom / 2;	

// 	isometric(&x, &y, z);
// 	isometric(&x1, &y1, z1);
// 	x_step = x1 - x;
// 	y_step = y1 - y;
// 	max = MAX(MOD(x_step), MOD(y_step));
// 	x_step /= max;
// 	y_step /= max;
// 	while ((int) (x - x1) || (int) (y - y1))
// 	{
// 		mlx_pixel_put(matrix->mlx_ptr, matrix->win_ptr, y + matrix->shift_y, x + matrix->shift_x, 0xffffff);
// 		x += x_step;
// 		y += y_step;
// 	}
// }

// void draw(t_mlx_data *matrix)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < matrix->width)
//     {
//         x = 0;
//         while (x < matrix->height)
//         {
// 			if (x < matrix->height - 1)
//             	bresenham(x, y, x + 1, y, matrix);
// 			if (y < matrix->width - 1)
//             	bresenham(x, y, x, y + 1, matrix);
//             x++;
//         }
//         y++;
//     }
// }
