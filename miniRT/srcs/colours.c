/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:51:24 by ppolinta          #+#    #+#             */
/*   Updated: 2024/09/21 19:21:41 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_rgb	hadamard_product(t_rgb *c1, t_rgb *c2)
{
	t_rgb	result;

	result.r = c1->r * c2->r;
	result.g = c1->g * c2->g;
	result.b = c1->b * c2->b;
	result.a = c1->a * c2->a;
	return (result);
}

t_rgb	add_colours(t_rgb *c1, t_rgb *c2)
{
	t_rgb	result;

	result.r = c1->r + c2->r;
	result.g = c1->g + c2->g;
	result.b = c1->b + c2->b;
	result.a = c1->a + c2->a;
	return (result);
}

t_rgb	subtract_colours(t_rgb *c1, t_rgb *c2)
{
	t_rgb	result;

	result.r = c1->r - c2->r;
	result.g = c1->g - c2->g;
	result.b = c1->b - c2->b;
	result.a = c1->a - c2->a;
	return (result);
}

t_rgb	multiply_colours(t_rgb *colour, float nbr)
{
	t_rgb	result;

	result.r = colour->r * nbr;
	result.g = colour->g * nbr;
	result.b = colour->b * nbr;
	result.a = colour->a * nbr;
	return (result);
}

t_rgb	divide_colours(t_rgb *colour, float nbr)
{
	t_rgb	result;

	result.r = colour->r / nbr;
	result.g = colour->g / nbr;
	result.b = colour->b / nbr;
	result.a = colour->a / nbr;
	return (result);
}
