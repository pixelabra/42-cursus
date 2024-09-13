/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:59:21 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/13 33:1:03 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_process(t_philo *philo)
{
	pthread_create(&philo->overseer_th, NULL, overseer, philo);
	pthread_create(&philo->death_th, NULL, death_checker, philo);
	cycle(philo);
	pthread_join(philo->overseer_th, NULL);
	pthread_join(philo->death_th, NULL);
	sem_closer(philo->data);
}

int	process_creator(t_data *data, t_philo *philos)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < philos->data->nbr_philos)
	{
		pid = fork();
		if (pid < 0)
		{
			free(philos);
			sem_destroyer(data);
			exit(1);
		}
		if (!pid)
		{
			philo_process(&philos[i]);
			free(philos);
			exit(0);
		}
	}
	i = -1;
	while (++i < data->nbr_philos)
		sem_wait(data->full);
	i = -1;
	while (++i < data->nbr_philos)
		sem_post(data->death);
	return (0);
}
