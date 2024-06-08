/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:43:52 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/06/08 17:44:06 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_rgb	get_rgb(unsigned int colour)
{
	t_rgb	rgb;

	rgb.a = (colour >> 24) & 0xFF;
	rgb.r = (colour >> 16) & 0xFF;
	rgb.g = (colour >> 8) & 0xFF;
	rgb.b = (colour >> 0) & 0xFF;
	return (rgb);
}

unsigned int	interpolate_colour(t_rgb start_rgb, t_rgb end_rgb, float t)
{
	t_rgb			rgb;
	unsigned int	colour;

	rgb.r = (unsigned char)(start_rgb.r + t * (end_rgb.r - start_rgb.r));
	rgb.g = (unsigned char)(start_rgb.g + t * (end_rgb.g - start_rgb.g));
	rgb.b = (unsigned char)(start_rgb.b + t * (end_rgb.b - start_rgb.b));
	rgb.a = (unsigned char)(start_rgb.a + t * (end_rgb.a - start_rgb.a));
	colour = ((rgb.a << 24) | (rgb.r << 16) | (rgb.g << 8) | (rgb.b << 0));
	return (colour);
}
