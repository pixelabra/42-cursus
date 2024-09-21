/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:25:20 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/21 19:54:23 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	destroy_all(t_data *data, int e)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	exit(e);
}

int	exit_button(t_data *data)
{
	ft_putendl_fd("miniRT exited.", 1);
	destroy_all(data, 0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	if ((keysym == W_KEY || keysym == A_KEY
			|| keysym == S_KEY || keysym == D_KEY))
		ft_putendl_fd("temp.", 1);

	if ((keysym == UP || keysym == DOWN
			|| keysym == LEFT || keysym == RIGHT))
		ft_putendl_fd("temp.", 1);
	if (keysym == ESC)
	{
		ft_putendl_fd("miniRT exited.", 1);
		destroy_all(data, 0);
	}
	return (0);
}

int	main(void)
{
	t_data	*data;

	data = init_mlx_data();
	draw(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &on_keypress, data);
	mlx_hook(data->win_ptr, 17, 1L << 2, &exit_button, data);
	mlx_loop(data->mlx_ptr);
}

// int	main(void)
// {
// 	t_vect p = create_vect(1, 4, -3, 1);
// 	t_vect v = create_vect(3, 3, 9, 0);
// 	t_vect new = add_point_and_vector(&p, &v);
// 	print_vect(p, "P");
// 	print_vect(v, "V");
// 	print_vect(new, "P + V");
// 	t_vect *mt = new_vect(1, 1, 1, 0);
// 	*mt = subtract_point_and_vector(mt, &v);
// 	print_vect(*mt, "Malloc'd point");
// 	*mt = create_vect(2, 5, 3, 0);
// 	print_vect(*mt, "Malloc'd vector - V");
// 	free(mt);
// 	print_vect(multiply_vect(&p, 2.5), "P * 2.5");
// 	print_vect(multiply_vect(&p, 0.25), "P * 0.25");
// 	print_vect(divide_vect(&v, 2), "V / 2");
// 	print_vect(divide_vect(&v, 0.5), "V / 0.5");
// 	print_vect(divide_vect(&v, 0), "V / 0");
// }
