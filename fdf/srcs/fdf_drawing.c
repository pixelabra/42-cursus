/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:37:54 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/25 17:32:16 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
			value = (int) str[i] - '0' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = (int) str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = (int) str[i] - 'A' + 10;
		else
			break ;
		result = (result * 16) + value;
		i++;
	}
	return (result);
}

unsigned int	colour(t_coord start, t_coord end)
{
	(void) start;
	(void) end;
	return (0xFFFFFF);
}

void	create_image(t_mlx_data *data)
{
	// int		i;
	// int		j;
	// int 	colour;
	// char	*pixel_addr;

	// colour = 0x000000;
	if (data->img.img_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = NULL;
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	// j = -1;
	// while (++j < data->img.height)
	// {
	// 	i = -1;
	// 	while (++i < data->img.width)
	// 	{
	// 		// colour = calculate_colour(i, j, data->img.width, data->img.height);
	// 		pixel_addr = data->img.addr + (j * data->img.line_length + i * (data->img.bits_per_pixel / 8));
	// 		if (data->img.endian == 0)	
    //             *(unsigned int*)pixel_addr = mlx_get_color_value(data->mlx_ptr, colour);
	// 	}
	// }
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
