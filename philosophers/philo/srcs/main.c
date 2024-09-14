/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:48 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 16:47:05 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_philo *philos, pthread_mutex_t *forks, int *flags)
{
	if (philos)
		free(philos);
	if (forks)
		free(forks);
	if (flags)
		free(flags);
}

int	allocator(t_data *data, t_philo **philos,
		pthread_mutex_t **forks, int **flags)
{
	*philos = malloc(sizeof(t_philo) * data->nbr_philos);
	*forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	*flags = malloc(sizeof(int) * data->nbr_philos);
	if (!*philos || !*forks || !*flags)
	{
		printf(MAGENTA BOLD"Shockingly, "RED BOLD"malloc failed.\n"RESET);
		free_all(*philos, *forks, *flags);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*flags;

	if (init_data(&data, ac, av))
		return (1);
	if (allocator(&data, &philos, &forks, &flags)
		|| init_mtx(&data, forks) || init_flags(&data, flags)
		|| init_philos(&data, philos, forks, flags))
	{
		mtx_destroyer(&data, forks);
		free_all(philos, forks, flags);
		return (1);
	}
	thread_creator(&data, philos);
	mtx_destroyer(&data, forks);
	free_all(philos, forks, flags);
	return (0);
}
