
#include "../../inc/minirt.h"
#include <sys/time.h>
#include <inttypes.h>

size_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		ft_putendl_fd("Could not get time of day\n", 2);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	drawpximg(t_data *data, int i, int j, t_rgb colour)
{
	char	*pixel_addr;

	if (i < 0 || i > WIN_WIDTH || j < 0 || j > WIN_HEIGHT)
		return ;
	pixel_addr = data->img.addr + (j * data->img.line_length
			+ i * (data->img.bits_per_pixel / 8));
	*(unsigned int *) pixel_addr = mlx_get_color_value
		(data->mlx_ptr, rgb_to_uint(colour));
}

t_vect	calc_world_point(int p, double wall_size)
{
	t_vect	result;

	result.x = -(wall_size / 2) + (wall_size / WIN_HEIGHT) * (p % WIN_WIDTH);
	result.y = (wall_size / 2) - (wall_size / WIN_HEIGHT) * (p / WIN_WIDTH);
	result.z = 10;
	result.w = 1;
	return (result);
}

t_rgb	get_pixel_colour(t_data *data, int i, int j)
{
	unsigned int	color_value;

	if (i < 0 || i >= WIN_WIDTH || j < 0 || j >= WIN_HEIGHT)
		return ((t_rgb){0, 0, 0, 0});
	color_value = *(unsigned int *)(data->img.addr + (j * data->img.line_length + i * (data->img.bits_per_pixel / 8)));
	return (get_rgb(color_value));
}

t_rgb get_weighted_colour_after(t_data *data, int p)
{
	t_rgb	prev;
	t_rgb	next;
	t_rgb	guess;
	t_simd	simd;
	double	result[4];

	prev = get_pixel_colour(data, p % WIN_WIDTH - 1, p / WIN_WIDTH);
	next = get_pixel_colour(data, p % WIN_WIDTH + 2, p / WIN_WIDTH);
	simd.r1 = _mm256_setr_pd(0, (double)prev.b, (double)prev.g, (double)prev.r);
	simd.r2 = _mm256_setr_pd(0, (double)next.b, (double)next.g, (double)next.r);
	simd.r3 = _mm256_set1_pd(0.6666666666666666);
	simd.r4 = _mm256_set1_pd(0.3333333333333333);
	simd.r1 = _mm256_mul_pd(simd.r1, simd.r3);
	simd.r2 = _mm256_mul_pd(simd.r2, simd.r4);
	simd.r1 = _mm256_add_pd(simd.r1, simd.r2);
	_mm256_storeu_pd(result, simd.r1);
	guess.r = (int)(result[3] + 0.5);
	guess.g = (int)(result[2] + 0.5);
	guess.b = (int)(result[1] + 0.5);
	guess.a = 0;
	return (guess);
}

t_rgb get_weighted_colour_before(t_data *data, int p)
{
	t_rgb	prev;
	t_rgb	next;
	t_rgb	guess;
	t_simd	simd;
	double	result[4];

	prev = get_pixel_colour(data, p % WIN_WIDTH - 2, p / WIN_WIDTH);
	next = get_pixel_colour(data, p % WIN_WIDTH + 1, p / WIN_WIDTH);
	simd.r1 = _mm256_setr_pd(0, (double)next.b, (double)next.g, (double)next.r);
	simd.r2 = _mm256_setr_pd(0, (double)prev.b, (double)prev.g, (double)next.r);
	simd.r3 = _mm256_set1_pd(0.6666666666666666);
	simd.r4 = _mm256_set1_pd(0.3333333333333333);
	simd.r1 = _mm256_mul_pd(simd.r1, simd.r3);
	simd.r2 = _mm256_mul_pd(simd.r2, simd.r4);
	simd.r1 = _mm256_add_pd(simd.r1, simd.r2);
	_mm256_storeu_pd(result, simd.r1);
	guess.r = (int)(result[3] + 0.5);
	guess.g = (int)(result[2] + 0.5);
	guess.b = (int)(result[1] + 0.5);
	guess.a = 0;
	return (guess);
}

t_rgb get_weighted_colour_below(t_data *data, int p)
{
	t_rgb	prev;
	t_rgb	next;
	t_rgb	guess;
	t_simd	simd;
	double	result[4];

	prev = get_pixel_colour(data, p % WIN_WIDTH, p / WIN_WIDTH - 1);
	next = get_pixel_colour(data, p % WIN_WIDTH, p / WIN_WIDTH + 2);
	simd.r1 = _mm256_set_pd(0, (double)next.b, (double)next.g, (double)next.r);
	simd.r2 = _mm256_set_pd(0, (double)prev.b, (double)prev.g, (double)prev.r);
	simd.r3 = _mm256_set1_pd(0.6666666666666666);
	simd.r4 = _mm256_set1_pd(0.3333333333333333);
	simd.r1 = _mm256_mul_pd(simd.r1, simd.r3);
	simd.r2 = _mm256_mul_pd(simd.r2, simd.r4);
	simd.r1 = _mm256_add_pd(simd.r1, simd.r2);
	_mm256_storeu_pd(result, simd.r1);
	guess.r = (int)(result[3] + 0.5);
	guess.g = (int)(result[2] + 0.5);
	guess.b = (int)(result[1] + 0.5);
	guess.a = 0;
	return (guess);
}

t_rgb get_weighted_colour_above(t_data *data, int p)
{
	t_rgb	prev;
	t_rgb	next;
	t_rgb	guess;
	t_simd	simd;
	double	result[4];

	prev = get_pixel_colour(data, p % WIN_WIDTH, p / WIN_WIDTH - 2);
	next = get_pixel_colour(data, p % WIN_WIDTH, p / WIN_WIDTH + 1);
	simd.r1 = _mm256_set_pd(0, (double)prev.b, (double)prev.g, (double)prev.r);
	simd.r2 = _mm256_set_pd(0, (double)next.b, (double)next.g, (double)next.r);
	simd.r3 = _mm256_set1_pd(0.6666666666666666);
	simd.r4 = _mm256_set1_pd(0.3333333333333333);
	simd.r1 = _mm256_mul_pd(simd.r1, simd.r3);
	simd.r2 = _mm256_mul_pd(simd.r2, simd.r4);
	simd.r1 = _mm256_add_pd(simd.r1, simd.r2);
	_mm256_storeu_pd(result, simd.r1);
	guess.r = (int)(result[3] + 0.5);
	guess.g = (int)(result[2] + 0.5);
	guess.b = (int)(result[1] + 0.5);
	guess.a = 0;
	return (guess);
}

// t_rgb get_weighted_colour_after(t_data *data, int p)
// {
// 	int		x;
// 	int		y;
// 	t_rgb	prev;
// 	t_rgb	next;
// 	t_rgb	guess;

// 	x = p % WIN_WIDTH;
// 	y = p / WIN_WIDTH;
// 	prev = get_pixel_colour(data, x - 1, y);
// 	next = get_pixel_colour(data, x + 2, y);
// 	guess.r = (int)((next.r * 0.6666) + (prev.r * 0.3333) + 0.5);
// 	guess.g = (int)((next.g * 0.6666) + (prev.g * 0.3333) + 0.5);
// 	guess.b = (int)((next.b * 0.6666) + (prev.b * 0.3333) + 0.5);
// 	guess.a = 0;
// 	return (guess);
// }

// t_rgb get_weighted_colour_before(t_data *data, int p)
// {
// 	int		x;
// 	int		y;
// 	t_rgb	prev;
// 	t_rgb	next;
// 	t_rgb	guess;

// 	x = p % WIN_WIDTH;
// 	y = p / WIN_WIDTH;
// 	prev = get_pixel_colour(data, x - 2, y);
// 	next = get_pixel_colour(data, x + 1, y);
// 	guess.r = (int)((next.r * 0.6666) + (prev.r * 0.3333) + 0.5);
// 	guess.g = (int)((next.g * 0.6666) + (prev.g * 0.3333) + 0.5);
// 	guess.b = (int)((next.b * 0.6666) + (prev.b * 0.3333) + 0.5);
// 	guess.a = 0;
// 	return (guess);
// }

// t_rgb get_weighted_colour_below(t_data *data, int p)
// {
// 	int		x;
// 	int		y;
// 	t_rgb	prev;
// 	t_rgb	next;
// 	t_rgb	guess;

// 	x = p % WIN_WIDTH;
// 	y = p / WIN_WIDTH;
// 	prev = get_pixel_colour(data, x, y - 1);
// 	next = get_pixel_colour(data, x, y + 2);
// 	guess.r = (int)((next.r * 0.6666) + (prev.r * 0.3333) + 0.5);
// 	guess.g = (int)((next.g * 0.6666) + (prev.g * 0.3333) + 0.5);
// 	guess.b = (int)((next.b * 0.6666) + (prev.b * 0.3333) + 0.5);
// 	guess.a = 0;
// 	return (guess);
// }

// t_rgb get_weighted_colour_above(t_data *data, int p)
// {
// 	int		x;
// 	int		y;
// 	t_rgb	prev;
// 	t_rgb	next;
// 	t_rgb	guess;

// 	x = p % WIN_WIDTH;
// 	y = p / WIN_WIDTH;
// 	prev = get_pixel_colour(data, x, y - 2);
// 	next = get_pixel_colour(data, x, y + 1);
// 	guess.r = (int)((prev.r * 0.6666) + (next.r * 0.3333) + 0.5);
// 	guess.g = (int)((prev.g * 0.6666) + (next.g * 0.3333) + 0.5);
// 	guess.b = (int)((prev.b * 0.6666) + (next.b * 0.3333) + 0.5);
// 	guess.a = 0;
// 	return (guess);
// }

void	*draw_thread(void *vdata)
{
	t_draw		d;
	static int	incr;

	d.data = (t_data *)vdata;
	d.total_pixels = d.data->cam.vsize * d.data->cam.hsize;
	pthread_mutex_lock(&d.data->draw_mutex);
	d.p = d.total_pixels / N_THREADS * incr;
	incr++;
	pthread_mutex_unlock(&d.data->draw_mutex);
	d.upper_bound = d.p + d.total_pixels / N_THREADS;
	while (d.p < d.upper_bound)
	{
		if ((d.p / WIN_WIDTH) % 3 == 0)
		{
			d.local_ray = ray_for_pxl(&d.data->cam, d.p);
			d.colour = colour_at(&d.data->world, &d.local_ray, 4);
			d.ambient = hadamard_product(&d.data->world.ambient_light, &d.colour);
			if (!d.data->world.settings.superfast)
				d.colour = add_colours(&d.colour, &d.ambient);
			drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
		}
		d.p += 3;
	}
	// d.p = d.total_pixels / N_THREADS * (incr - 1);
	// while (d.p < d.upper_bound)
	// {
	// 	if ((d.p / WIN_WIDTH) % 3 == 0)
	// 	{
	// 		if ((d.p % WIN_WIDTH) % 3 == 1)
	// 			d.colour = get_weighted_colour_after(d.data, d.p);
	// 		else if ((d.p % WIN_WIDTH) % 3 == 2)
	// 			d.colour = get_weighted_colour_before(d.data, d.p);
	// 		drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
	// 	}
	// 	d.p++;
	// }
	// d.p = d.total_pixels / N_THREADS * (incr - 1);
	// while (d.p < d.upper_bound)
	// {
	// 	if ((d.p / WIN_WIDTH) % 3 != 0)
	// 	{
	// 		if ((d.p / WIN_WIDTH) % 3 == 1)
	// 			d.colour = get_weighted_colour_below(d.data, d.p);
	// 		else if ((d.p / WIN_WIDTH) % 3 == 2)
	// 			d.colour = get_weighted_colour_above(d.data, d.p);
	// 		drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
	// 	}
	// 	d.p++;
	// }
	if (incr == N_THREADS)
		incr = 0;
	return (NULL);
}

// void *draw_thread(void *vdata)
// {
// 	t_draw		d;
// 	static int	incr;
// 	int			x;
// 	int			y;
// 	t_rgb 		prev;
// 	t_rgb 		next;

// 	d.data = (t_data *)vdata;
// 	d.total_pixels = d.data->cam.vsize * d.data->cam.hsize;
// 	pthread_mutex_lock(&d.data->draw_mutex);
// 	d.p = d.total_pixels / N_THREADS * incr;
// 	incr++;
// 	pthread_mutex_unlock(&d.data->draw_mutex);
// 	d.upper_bound = d.p + d.total_pixels / N_THREADS;
//     while (d.p < d.upper_bound)
//     {
// 		x = d.p % WIN_WIDTH;
// 		y = d.p / WIN_WIDTH;
// 		if (y % 2 == 0 && x % 2 == 0)
//         {
//             d.local_ray = ray_for_pxl(&d.data->cam, d.p);
//             d.colour = colour_at(&d.data->world, &d.local_ray, 4);
//             d.ambient = hadamard_product(&d.data->world.ambient_light, &d.colour);
//             if (!d.data->world.settings.superfast)
//                 d.colour = add_colours(&d.colour, &d.ambient);
//             drawpximg(d.data, x, y, d.colour);
//         }
//         d.p++;
//     }
// 	d.p = d.total_pixels / N_THREADS * (incr - 1);
// 	while (d.p < d.upper_bound)
// 	{
// 		x = d.p % WIN_WIDTH;
// 		y = d.p / WIN_WIDTH;
// 		if (y % 2 == 0 && x % 2 == 1)
//         {
// 			prev = get_pixel_colour(d.data, x - 1, y);
// 			next = get_pixel_colour(d.data, x + 1, y);
// 			d.colour.r = (prev.r + next.r) / 2.0;
// 			d.colour.g = (prev.g + next.g) / 2.0;
// 			d.colour.b = (prev.b + next.b) / 2.0;
// 			d.colour.a = 0;
// 			drawpximg(d.data, x, y, d.colour);
// 		}
// 		d.p++;
// 	}
// 	d.p = d.total_pixels / N_THREADS * (incr - 1);
// 	while (d.p < d.upper_bound)
// 	{
// 		x = d.p % WIN_WIDTH;
// 		y = d.p / WIN_WIDTH;
// 		if (y % 2 == 1)
// 		{
// 			prev = get_pixel_colour(d.data, x, y - 1);
// 			next = get_pixel_colour(d.data, x, y + 1);
//             d.colour.r = (prev.r + next.r) / 2.0;
//             d.colour.g = (prev.g + next.g) / 2.0;
//             d.colour.b = (prev.b + next.b) / 2.0;
//             d.colour.a = 0;
//         	drawpximg(d.data, d.p % WIN_WIDTH, y, d.colour);
//         }
//         d.p++;
//     }
// 	if (incr == N_THREADS)
// 		incr = 0;
// 	return (NULL);
// }

void	draw(t_data *data)
{
	pthread_t	t[N_THREADS];
	int			i;
	size_t		start_time;
	size_t		end_time;

	start_time = get_time();
	create_image(data);
	i = 0;
	while (i < N_THREADS)
		pthread_create(&t[i++], NULL, draw_thread, data);
	i = 0;
	while (i < N_THREADS)
		pthread_join(t[i++], NULL);
		
	t_draw	d;
	d.data = data;
	d.p = 1;
	d.total_pixels = d.data->cam.vsize * d.data->cam.hsize;
	while (d.p < d.total_pixels)
	{
		d.colour = (t_rgb){0,0,0,0};
		if ((d.p / WIN_WIDTH) % 3 == 0)
		{
			if ((d.p % WIN_WIDTH) % 3 == 1)
			{
				d.colour = get_weighted_colour_after(d.data, d.p);
				drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
			}
			else if ((d.p % WIN_WIDTH) % 3 == 2)
			{
				d.colour = get_weighted_colour_before(d.data, d.p);
				drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
			}
		}
		d.p++;
	}
	d.p = 0;
	while (d.p < d.total_pixels)
	{
		d.colour = (t_rgb){0,0,0,0};
		if ((d.p / WIN_WIDTH) % 3 != 0)
		{
			if ((d.p / WIN_WIDTH) % 3 == 1)
			{
				d.colour = get_weighted_colour_below(d.data, d.p);
				// drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
			}
			else if ((d.p / WIN_WIDTH) % 3 == 2)
			{
				d.colour = get_weighted_colour_above(d.data, d.p);
			}
			drawpximg(d.data, d.p % WIN_WIDTH, d.p / WIN_WIDTH, d.colour);
		}
		d.p++;
	}

	end_time = get_time();
	printf("Render time: %ld milliseconds\n", end_time - start_time);
	mlx_put_image_to_window
		(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}
