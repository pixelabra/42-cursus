/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:48 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/13 00:54:56 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	allocator(t_data *data, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!*philos)
	{
		printf(MAGENTA BOLD"Shockingly, "RED BOLD"malloc failed.\n"RESET);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philos;

	if (init_data(&data, ac, av))
		return (1);
	if (allocator(&data, &philos) || init_semaphores(&data)
		|| init_philos(&data, philos))
	{
		sem_destroyer(&data);
		free(philos);
		return (1);
	}
	process_creator(&data, philos);
	sem_destroyer(&data);
	free(philos);
	return (0);
}
