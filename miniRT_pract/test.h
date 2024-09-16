#ifndef TEST_H

# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// Initial structure of vector
typedef struct s_Vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

double	sqr(double nbr);
double	v_lengthsq(t_vect vect);
double	v_length(t_vect vect);
double	v_normalise(t_vect *vect);
t_vect	*v_normalised(t_vect *vect);
t_vect	*v_addition(t_vect v1, t_vect v2);
void	v_multiply(t_vect *vect, double nbr);
t_vect	*v_mult(t_vect  v1, double nbr);
double	v_dot(t_vect v1, t_vect v2);
t_vect	*v_cross(t_vect v1, t_vect v2);
t_vect	*v_copy(t_vect v1);

#endif