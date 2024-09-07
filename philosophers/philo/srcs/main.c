/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:48 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 02:27:28 by a3y3g1           ###   ########.fr       */
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

int	allocator(t_data *data, t_philo **philos, pthread_mutex_t **forks, int **flags)
{
	// philos = NULL;
	// forks = NULL;
	// flags = NULL;
	*philos = malloc(sizeof(t_philo) * data->nbr_philos);
	printf("this is allocator: %p\n", philos);
	*forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	printf("this is allocator: %p\n", forks);
	*flags = malloc(sizeof(int) * data->nbr_philos);
	printf("this is allocator: %p\n", flags);
	if (!(*philos) || !*forks || !*flags)
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

	// data = NULL;
	philos = NULL;
	flags = NULL;
	forks = NULL;
	if (init_data(&data, ac, av))
		return (1);
	// if (allocator(&data, philos, forks, flags)
	// 	|| init_mtx(&data, forks) || init_flags(&data, flags)
	// 	|| init_philos(&data, philos, forks, flags))
	// {
	// 	mtx_destroyer(&data, forks);
	// 	free_all(philos, forks, flags);
	// 	return (1);
	// }
	allocator(&data, &philos, &forks, &flags);
	printf("this is main: %p\n", philos);
	printf("this is main: %p\n", forks);
	printf("this is main: %p\n", flags);
	mtx_destroyer(&data, forks);
	free_all(philos, forks, flags);
	return (0);
}
