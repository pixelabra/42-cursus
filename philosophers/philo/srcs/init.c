/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:47:49 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 02:16:06 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	mtx_destroyer(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->meals);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->nbr_philos)
	{
		// printf("this is destroyer: %p\n", forks);
		pthread_mutex_destroy(&forks[0]);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || input_checker(data, av))
	{
		printf(RED BOLD"Invalid input!\n"
			CYAN"./philo <nbr_philos> <t_death> <t_eat> <t_sleep> <nbr_meals>\n"
			YELLOW"All inputs must be integers.\n"RESET);
		return (1);
	}
	data->t_genesis = get_time();
	return (0);
}

int	init_mtx(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (!pthread_mutex_init(&data->death, NULL))
		return (mtx_destroyer(data, forks));
	if (!pthread_mutex_init(&data->meals, NULL))
		return (mtx_destroyer(data, forks));
	if (!pthread_mutex_init(&data->time, NULL))
		return (mtx_destroyer(data, forks));
	if (!pthread_mutex_init(&data->print, NULL))
		return (mtx_destroyer(data, forks));
	i = 0;
	while (i < data->nbr_philos)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (mtx_destroyer(data, forks));
	return (0);
}

int	init_flags(t_data *data, int *flags)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
		flags[i++] = 0;
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks, int *flags)
{
	// int	i;

	// i = 0;
	// while (i < data->nbr_philos)
	// {
		
	// }
	(void) data;
	(void) philos;
	(void) forks;
	(void) flags;
	return (0);
}
