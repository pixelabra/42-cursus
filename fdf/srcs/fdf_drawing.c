/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/25 02:29:47 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

void isometric(float *x, float *y, int z)
{
    float original_x = *x;
    float original_y = *y;
    *x = (original_x - original_y) * cos(1);
    *y = (original_x + original_y) * sin(1) - z;
}


void	bresenham(float x, float y, float x1, float y1, mlx_data* matrix)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;

	z = matrix->matrix[(int) x][(int) y];
	z1 = matrix->matrix[(int) x1][(int) y1];


	x *= matrix->zoom;
	y *= matrix->zoom;
	z *= matrix->zoom / 5;
	y1 *= matrix->zoom;
	x1 *= matrix->zoom;
	z1 *= matrix->zoom / 5;

	// x += matrix->shift_x;
	// y += matrix->shift_y;

	matrix->colour = (z || z1) ? 0xe80c0c : 0xffffff; 
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int) (x - x1) || (int) (y - y1))
	{
		mlx_pixel_put(matrix->connection, matrix->win, y + matrix->shift_y, x + matrix->shift_x, matrix->colour);
		x += x_step;
		y += y_step;
	}
}

void draw(mlx_data *matrix)
{
    int x;
    int y;

    y = 0;
    while (y < matrix->length)
    {
        x = 0;
        while (x < matrix->width)
        {
			if (x < matrix->width - 1)
            	bresenham(x, y, x + 1, y, matrix);
			if (y < matrix->length - 1)
            	bresenham(x, y, x, y + 1, matrix);
            x++;
        }
        y++;
    }
}
