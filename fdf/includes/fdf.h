/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:51:56 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/04/25 01:58:35 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx_PxAb/mlx.h"
# include "../libft/libft.h"

typedef struct matrix_data 
{
	int		**matrix;
	int		length;
	int		width;
	int		zoom;
	int		colour;
	void	*connection;
	void	*win;
}	mlx_data;

void	ft_error(int error_code, char *str);
int		get_width(char **argv);
int		get_length(char **argv);
void	build_matrix(mlx_data *mx_var, char **argv);
void	pop_matrix(int *row, char *line);
void	bresenham(float x, float y, float x1, float y1, mlx_data* matrix);
void 	draw(mlx_data *matrix);
void 	isometric(float *x, float *y, int z);

#endif