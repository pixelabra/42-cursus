/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:16:18 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 17:26:54 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_process(t_philo *philo, t_philo *philos)
{
	pthread_create(&philo->overseer_th, NULL, overseer, philo);
	pthread_create(&philo->death_th, NULL, death_checker, philo);
	cycle(philo);
	pthread_join(philo->overseer_th, NULL);
	pthread_join(philo->death_th, NULL);
	sem_closer(philo->data);
	free(philos);
	exit(0);
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
			philo_process(&philos[i], philos);
	}
	i = -1;
	while (++i < data->nbr_philos)
		sem_wait(data->full);
	i = -1;
	while (++i < data->nbr_philos)
		sem_post(data->death);
	return (0);
}
