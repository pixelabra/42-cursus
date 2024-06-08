/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:51:56 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 20:33:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"

# ifdef __APPLE__
#  define WIN_WIDTH 1000
#  define WIN_HEIGHT 1000
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_Q 12
#  define KEY_A 0
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_E 14
#  define KEY_D 2
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_R 15
#  define KEY_P 35
#  define KEY_I 34
#  define KEY_R_PLUS 18
#  define KEY_R_MINUS 19
#  define KEY_G_PLUS 20
#  define KEY_G_MINUS 21
#  define KEY_B_PLUS 23
#  define KEY_B_MINUS 22
# else
#  define WIN_WIDTH 1000
#  define WIN_HEIGHT 1000
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_Q 113
#  define KEY_A 97
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_E 101
#  define KEY_D 100
#  define KEY_Z 122
#  define KEY_X 120
#  define KEY_R 114
#  define KEY_P 112
#  define KEY_I 105
#  define KEY_R_PLUS 49
#  define KEY_R_MINUS 50
#  define KEY_G_PLUS 51
#  define KEY_G_MINUS 52
#  define KEY_B_PLUS 53
#  define KEY_B_MINUS 54
# endif

typedef enum e_projection
{
	ISOMETRIC,
	PARALLEL,
	CONIC
}	t_projection;

typedef enum e_colour
{
	R,
	G,
	B
}	t_colour;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_rgb;

// 3D coordinate
typedef struct s_coord
{
	int				x;
	int				y;
	int				z;
	unsigned int	colour;
}	t_coord;

// Image specific details
typedef struct s_image
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}	t_image;

typedef struct s_br_param
{
	int				x_step;
	int				y_step;
	int				decision;
	int				abs_dx;
	int				abs_dy;
	int				curr_step;
	int				total_steps;
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

void			ft_error(int error_code, char *str, int fd_map);
int				get_height(char **argv);
int				get_width(char **argv);
void			build_matrix(t_mlx_data *mx_var, char **argv);
int				pop_matrix(t_coord *row, char *line, int current_line, int i);

int				br_max(int abs_dx, int abs_dy);
t_rgb			get_rgb(unsigned int colour);
unsigned int	interpolate_colour(t_rgb start_rgb, t_rgb end_rgb, float t);

int				br_abs(int number);
void			br_algo(t_mlx_data *data, t_coord start, t_coord end);
void			br_inc(t_coord *start, t_br_param *params, int decision2x);
t_br_param		br_setup(t_coord start, t_coord end);
int				br_step(int start, int end);
void			zoomer(t_coord *coord, t_mlx_camera *config);

void			create_image(t_mlx_data *data);
void			drawpximg(t_mlx_data *data, t_coord start, unsigned int colour);
void			draw(t_mlx_data *data);

void			isometric(t_coord *coord, t_mlx_camera *config);
void			parallel(t_coord *coord, t_mlx_camera *config);

t_mlx_data		*init_mlx_data(void);
int				close_window(t_mlx_data *data);
void			free_data(t_mlx_data *data);
void			transform_points(t_mlx_data *data, t_coord **temp_matrix);
void			file_checker(char **argv);
void			check_map_formatting(int fd_map, int exp_width, char **argv);
int				read_first_line(int fd_map, char **line);
void			check_file_ext(char *file_name);
t_coord			**create_tmp_matrix(t_coord **og_matrix, int width, int height);
void			free_matrix(t_coord **matrix, int height);
void			init_config(t_mlx_camera *config, t_mlx_camera *init_config);
void			reset(t_mlx_camera *config, t_mlx_camera *init_config);

void			rotation_x(t_coord *coord, t_mlx_camera *config);
void			rotation_y(t_coord *coord, t_mlx_camera *config);
void			rotation_z(t_coord *coord, t_mlx_camera *config);

void			adj_colours(t_mlx_data *data, t_colour colour_change, int incr);

void			handle_movement(int keycode, t_mlx_data *data);
void			handle_projection(int keycode, t_mlx_data *data);
void			handle_rotation(int keycode, t_mlx_data *data);
void			handle_features(int keycode, t_mlx_data *data);
int				deal_key(int keycode, t_mlx_data *data);
int				free_array(char **point);
int				ft_htoi(char *str);
void			pop_colour(t_coord *row, char *points, int i);

void			init_null(t_mlx_data *data);
void			free_init(t_mlx_data *data);
void			alloc_matrix(t_mlx_data *data, char **argv, int fd_map);

#endif