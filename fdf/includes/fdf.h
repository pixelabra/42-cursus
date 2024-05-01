/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:51:56 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/02 00:58:33 by a3y3g1           ###   ########.fr       */
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

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

// 3D coordinate
typedef struct s_coord
{
	int			x;
	int			y;
	int				z;
	unsigned int	colour;
}	t_coord;

// Image specific details
typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;


// MLX instance, window, image, matrix information
typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	t_coord	**matrix;
	int		width;
	int		height;
	float	zoom;
	int		shift_x;
	int		shift_y;
}	t_mlx_data;

void	ft_error(int error_code, char *str);
int		get_height(char **argv);
int		get_width(char **argv);
void	build_matrix(t_mlx_data *mx_var, char **argv);
void	pop_matrix(t_coord *row, char *line, int current_line);
void	create_image(t_mlx_data *data);
unsigned int	colour(t_coord start, t_coord end);
void	draw_pixel_to_image(t_mlx_data *data, t_coord start, unsigned int colour);
void	bresenham_algo(t_mlx_data *data, t_coord start, t_coord end);
// int		calculate_colour(int i,int j, int img_width, int img_height);
// void	bresenham(float x, float y, float x1, float y1, t_mlx_data *matrix);
// void	draw(t_mlx_data *matrix);
// void	isometric(float *x, float *y, int z);
#endif