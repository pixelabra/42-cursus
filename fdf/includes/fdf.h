/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:51:56 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/05/25 23:13:00 by a3y3g1           ###   ########.fr       */
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
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_Q 113
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_E 101
# define KEY_D 100
# define KEY_Z 122
# define KEY_X 120
# define KEY_R 114
# define KEY_P 112
# define KEY_I 105

typedef enum e_projection
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

// 3D coordinate
typedef struct s_coord
{
	float			x;
	float			y;
	float			z;
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

typedef struct s_br_param
{
	float	x_step;
	float	y_step;
	float	decision;
	float	abs_dx;
	float	abs_dy;
}	t_br_param;

// MLX instance, window, image, matrix information
typedef struct s_mlx_camera
{
	int				shift_y;
	int				shift_x;
	int				inc_z;
	int				zoom;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	t_projection	projection;
}	t_mlx_camera;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			img;
	t_coord			**matrix;
	t_mlx_camera	*config;
	t_mlx_camera	*init_config;
	int				width;
	int				height;	
}	t_mlx_data;

void			ft_error(int error_code, char *str);
int				get_height(char **argv);
int				get_width(char **argv);
void			build_matrix(t_mlx_data *mx_var, char **argv);
void			pop_matrix(t_coord *row, char *line, int current_line);
void			create_image(t_mlx_data *data);
unsigned int	colour(t_coord start, t_coord end);
void			draw_pixel_to_image(t_mlx_data *data, t_coord start, unsigned int colour);
void			bresenham_algo(t_mlx_data *data, t_coord start, t_coord end);
t_br_param		bresenham_setup(t_coord start, t_coord end);
float			bresenham_step(float start, float end);
float			br_abs(int number);
void			draw(t_mlx_data *data);
void			zoomer(t_coord *coord, t_mlx_camera *config);
// int				max_z(t_mlx_data *data);
void			isometric(t_coord *coord, t_mlx_camera *config);
void			parallel(t_coord *coord, t_mlx_camera *config);
t_mlx_data		*init_mlx_data();
int				close_window(t_mlx_data *data);
void			free_data(t_mlx_data *data);
void			transform_points(t_mlx_data *data, t_coord **temp_matrix);
void			file_checker(char **argv);
void			check_map_formatting(int fd_map, int exp_width, char **argv);
int				read_first_line(int fd_map, char **line);
void			check_file_ext(char *file_name);
t_coord			**create_temp_matrix(t_coord **original_matrix, int width, int height);
void			free_matrix(t_coord **matrix, int height);
void			init_config(t_mlx_camera *config, t_mlx_camera *init_config);
void			reset(t_mlx_camera *config, t_mlx_camera *init_config);

void			rotation_x(t_coord *coord, t_mlx_camera *config);
void			rotation_y(t_coord *coord, t_mlx_camera *config);
void			rotation_z(t_coord *coord, t_mlx_camera *config);

void			handle_movement(int	keycode, t_mlx_data *data);
void			handle_projection(int keycode, t_mlx_data *data);
void			handle_rotation(int	keycode, t_mlx_data *data);
void			handle_features(int	keycode, t_mlx_data *data);
int				deal_key(int keycode, t_mlx_data *data);
void			free_array(char **point);
int				ft_htoi(char *str);



// int			calculate_colour(int i,int j, int img_width, int img_height);
// void	isometric(float *x, float *y, int z);
#endif