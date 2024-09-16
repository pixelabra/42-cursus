/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:16:34 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 17:16:36 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		write(2, "gettimeofday function failed!\npewpew\n", 37);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ph_usleep(size_t t_ms)
{
	size_t	t_start;

	t_start = get_time();
	while ((get_time() - t_start) < t_ms)
		usleep(200);
}
