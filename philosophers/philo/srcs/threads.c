/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:43:37 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 16:03:58 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	thread_creator(t_data *data, t_philo *philos)
{
	int		i;
	t_philo	*temp_philo;

	i = -1;
	while (++i < data->nbr_philos)
	{
		temp_philo = &philos[i];
		pthread_create(&temp_philo->thread, NULL, cycle, temp_philo);
	}
	
	i = -1;
	while (++i < data->nbr_philos)
	{
		temp_philo = &philos[i];
		pthread_join(temp_philo->thread, NULL);
	}
	return (0);
}
