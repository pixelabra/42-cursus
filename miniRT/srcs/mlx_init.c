/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:36:09 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/21 19:55:39 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_data(t_data *data)
{
	(void) data;
}

void	free_init(t_data *data)
{
	free_data(data);
	ft_putendl_fd("Unbelievably, malloc failed.", 2);
	exit(1);
}

t_data	*init_mlx_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		free_init(data);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		free_init(data);
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->win_ptr)
		free_init(data);
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
	return (data);
}

void	create_image(t_data *data)
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
