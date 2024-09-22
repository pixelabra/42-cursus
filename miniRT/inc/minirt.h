/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:24:51 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/22 20:07:05 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[0;37m"
# define BOLD		"\x1b[1m"
# define RESET		"\x1b[0m"

# define POINT		1
# define VECTOR		0
# define EPSILON	0.00001f
# define DIMENSION	4

# define WIN_WIDTH	1600
# define WIN_HEIGHT	900

# ifdef __APPLE__
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define UP 126
#  define LEFT 123
#  define DOWN 125
#  define RIGHT 124
#  define ESC 53
# else
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define UP 65362
#  define LEFT 65361
#  define DOWN 65364
#  define RIGHT 65363
#  define ESC 65307
# endif

/*	Tuple with 4 units.
	W integer allows us to differentiate between
	points and vectors. Set to 1 for points and
	 0 for vectors. */
typedef union u_vect
{
	float	a[4];
	struct 
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}	t_vect;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_rgb;

typedef struct s_obj
{
	t_matrix	matrix;
	t_matrix	inverse;
	t_matrix	transpose;
	t_matrix	minor;
	t_matrix	rotation_x;
	t_matrix	rotation_y;
	t_matrix	rotation_z;
	t_matrix	cofactor;
	t_vect		translation;
	t_vect		scale;
	float		determinant;
	int			type;
}	t_obj;

typedef union u_matrix
{
	float	a[4][4];
	struct
	{
		t_vect	r1;
		t_vect	r2;
		t_vect	r3;
		t_vect	r4;
	};
	
}	t_matrix;

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

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}	t_data;


// TUPLE FUNCTIONS
t_vect	add_point_and_vector(t_vect *point, t_vect *vector);
t_vect	subtract_point_and_vector(t_vect *point, t_vect *vector);
t_vect	add_vectors(t_vect *v1, t_vect *v2);
t_vect	subtract_vectors(t_vect *v1, t_vect *v2);
t_vect	multiply_vect(t_vect *vect, float multiplier);
t_vect	divide_vect(t_vect *vect, float divisor);
void	print_vect(t_vect vect, char *name);
t_vect	normalise_vect(t_vect *vect);
t_vect	create_vect(float x, float y, float z, int w);
t_vect	*new_vect(float x, float y, float z, int w);
t_vect	error_vect(void);
int		compare_vects(t_vect *v1, t_vect *v2);
t_vect	*copy_vect(t_vect *vect);
float	dot_vect(t_vect *v1, t_vect *v2);
t_vect	cross_vect(t_vect *v1, t_vect *v2);

// UTILS
float	sqr(float nbr);
float	vect_lengthsq(t_vect *vect);
float	vect_length(t_vect *vect);
int		compare_float(float a, float b);
t_vect	get_column(t_matrix *m, int index);

// COLOURS
t_rgb	hadamard_product(t_rgb *c1, t_rgb *c2);
t_rgb	add_colours(t_rgb *c1, t_rgb *c2);

// IMAGE STUFF
void	draw(t_data *data);
t_rgb	add_colours(t_rgb *c1, t_rgb *c2);
t_rgb	subtract_colours(t_rgb *c1, t_rgb *c2);

// MLX INIT STUFF
void	create_image(t_data *data);
t_data	*init_mlx_data(void);

// FREE STUF
void	free_init(t_data *data);
void	free_data(t_data *data);
void	free_dblptr(void **dblptr);
#endif