/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:43:37 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/10 00:57:23 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	thread_creator(t_data *data, t_philo *philos)
{
	int			i;
	t_philo		*temp_philo;
	pthread_t	overseer_t;

	i = -1;
	while (++i < data->nbr_philos)
	{
		temp_philo = &philos[i];
		pthread_create(&temp_philo->thread, NULL, cycle, temp_philo);
	}
	pthread_create(&overseer_t, NULL, overseer, philos);
	i = -1;
	while (++i < data->nbr_philos)
	{
		temp_philo = &philos[i];
		pthread_join(temp_philo->thread, NULL);
	}
	pthread_join(overseer_t, NULL);
	return (0);
}
