/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:19 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/07 02:51:52 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_data(t_mlx_data *data)
{
	if (!data)
		return ;
	if (data->matrix)
		free_matrix(data->matrix, data->height);
	if (data->config)
		free(data->config);
	if (data->init_config)
		free(data->init_config);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
}

void	free_matrix(t_coord **matrix, int height)
{
	int	j;

	if (!matrix)
		return ;
	j = -1;
	while (++j < height)
	{
		if (matrix[j])
			free(matrix[j]);
	}
	free(matrix);
}

void	free_array(char **point)
{
	int	i;

	i = -1;
	while (point)
		free(point[++i]);
	free(point);
}

void	free_init(t_mlx_data *data)
{
	free_data(data);
	ft_putendl_fd("Unbelieveably, malloc failed.", 2);
	exit(0);
}
