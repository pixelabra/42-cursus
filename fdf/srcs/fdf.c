/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:40:35 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 18:13:49 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	close_window(t_mlx_data *data)
{
	free(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_mlx_data	*data;

	if (argc != 2)
		ft_error(5, NULL, -1);
	file_checker(argv);
	data = init_mlx_data();
	build_matrix(data, argv);
	draw(data);
	mlx_hook(data->win_ptr, 2, 1L >> 0, deal_key, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
