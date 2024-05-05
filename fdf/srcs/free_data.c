/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:19 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/05 23:00:43 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_data(t_mlx_data *data)
{
	int	j;

	j = -1;
	if (!data)
		return ;
	if (data->matrix)
	{
		while (++j < data->height)
		{
			if (data->matrix[j])
				free(data->matrix[j]);
		}
		free(data->matrix);
	}
	if (data->config)
		free(data->config);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data);
}
