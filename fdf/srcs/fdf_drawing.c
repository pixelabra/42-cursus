/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 22:35:16 by agodeanu         ###   ########.fr       */
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
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = (int)(str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = (int)(str[i] - 'a') + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = (int)(str[i] - 'A') + 10;
		else
			break ;
		result = (result * 16) + value;
		i++;
	}
	return (result);
}

void	adj_colours(t_mlx_data *data, t_colour colour_change, int incr)
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
			if (data->matrix[j][i].z != 0)
			{
				rgb = get_rgb(data->matrix[j][i].colour);
				if (colour_change == R)
					rgb.r = (rgb.r + incr) % 256;
				if (colour_change == G)
					rgb.g = (rgb.g + incr) % 256;
				if (colour_change == B)
					rgb.b = (rgb.b + incr) % 256;
				data->matrix[j][i].colour = ((rgb.a << 24) | (rgb.r << 16)
						| (rgb.g << 8) | (rgb.b << 0));
			}
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
	data->img.img_ptr = mlx_new_image
		(data->mlx_ptr, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr
		(data->img.img_ptr, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
}

t_coord	**create_tmp_matrix(t_coord **og_matrix, int width, int height)
{
	int		i;
	int		j;
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
			temp_matrix[j][i] = og_matrix[j][i];
	}
	return (temp_matrix);
}

void	draw(t_mlx_data *data)
{
	int		i;
	int		j;
	t_coord	**temp_matrix;

	j = -1;
	temp_matrix = create_tmp_matrix(data->matrix, data->width, data->height);
	if (!temp_matrix)
		free_init(data);
	create_image(data);
	transform_points(data, temp_matrix);
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			if (i < data->width - 1)
				br_algo(data, temp_matrix[j][i], temp_matrix[j][i + 1]);
			if (j < data->height - 1)
				br_algo(data, temp_matrix[j][i], temp_matrix[j + 1][i]);
		}
	}
	mlx_put_image_to_window
		(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	free_matrix(temp_matrix, data->height);
}
