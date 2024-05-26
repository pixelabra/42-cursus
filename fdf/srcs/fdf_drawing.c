/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/26 21:51:37 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_htoi(char *str)
{
	int	i;
	int	value;
	int	result;

	result = 0;
	value = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = (int) (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = (int) (str[i] - 'a') + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = (int) (str[i] - 'A') + 10;
		else
			break ;
		result = (result * 16) + value;
		i++;
	}
	return (result);
}

t_rgb	get_rgb(unsigned int colour)
{
	t_rgb	rgb;

	rgb.a = (colour >> 24) & 0xFF;
	rgb.r = (colour >> 16) & 0xFF;
	rgb.g = (colour >> 8) & 0xFF;
	rgb.b = (colour >> 0) & 0xFF;
	return (rgb);
}

unsigned int	interpolate_colour(t_rgb start_rgb, t_rgb end_rgb, float t)
{
	t_rgb	rgb;

	rgb.r = (unsigned char) (start_rgb.r + t * (end_rgb.r - start_rgb.r));
	rgb.g = (unsigned char) (start_rgb.g + t * (end_rgb.g - start_rgb.g));
	rgb.b = (unsigned char) (start_rgb.b + t * (end_rgb.b - start_rgb.b));
	rgb.a = (unsigned char) (start_rgb.a + t * (end_rgb.a - start_rgb.a));
	unsigned int colour = ((rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | (rgb.b << 0));
	return (colour);
}

void	adjust_colours(t_mlx_data *data, t_colour colour_change, int increment)
{
	int		i;
	int		j;
	t_rgb	rgb;

	j = -1;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			rgb = get_rgb(data->matrix[j][i].colour);
			if (colour_change == R)
				rgb.r = (rgb.r + increment) % 256;
			if (colour_change == G)
				rgb.g = (rgb.g + increment) % 256;
			if (colour_change == B)
				rgb.b = (rgb.b + increment) % 256;
			data->matrix[j][i].colour = ((rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | (rgb.b << 0));
		}
	}
}

void	create_image(t_mlx_data *data)
{
	if (data->img.img_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = NULL;
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

t_coord			**create_temp_matrix(t_coord **original_matrix, int width, int height)
{
	int	i;
	int	j;
	t_coord	**temp_matrix;

	temp_matrix = malloc(sizeof(t_coord *) * height);
	if (!temp_matrix)
		return (NULL);
	j = -1;
	while (++j < height)
	{
		temp_matrix[j] = malloc(sizeof(t_coord) * width);
		if (!temp_matrix[j])
		{
			free_matrix(temp_matrix, height);
			return (NULL);
		}
		i = -1;
		while (++i < width)
			temp_matrix[j][i] = original_matrix[j][i];
	}
	return (temp_matrix);
}

void	draw(t_mlx_data *data)
{
	int	i;
	int	j;
	t_coord	**temp_matrix;

	j = -1;
	temp_matrix = create_temp_matrix(data->matrix, data->width, data->height);
	if (!temp_matrix)
		free_data(data);
	create_image(data);
	transform_points(data, temp_matrix); //change!
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			if (i < data->width - 1)
				bresenham_algo(data, temp_matrix[j][i], temp_matrix[j][i + 1]);
			if (j < data->height - 1)
				bresenham_algo(data, temp_matrix[j][i], temp_matrix[j + 1][i]);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	free_matrix(temp_matrix, data->height);
}
