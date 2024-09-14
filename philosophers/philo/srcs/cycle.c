/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:50:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 16:46:24 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	exit_flag_check(t_philo *philo)
{
	int	exit_return;

	pthread_mutex_lock(&philo->data->exit_mtx);
	exit_return = philo->data->exit_flag;
	pthread_mutex_unlock(&philo->data->exit_mtx);
	return (exit_return);
}

void	eat_cycle(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->ate == 0)
		ph_usleep(philo->data->t_eat / 2);
	get_forks(philo);
	ph_print(philo, EATING);
	pthread_mutex_lock(&philo->data->time_mtx);
	philo->t_lastmeal = get_time();
	pthread_mutex_unlock(&philo->data->time_mtx);
	pthread_mutex_lock(&philo->data->meals_mtx);
	philo->ate++;
	pthread_mutex_unlock(&philo->data->meals_mtx);
	ph_usleep(philo->data->t_eat);
}

void	sleep_cycle(t_philo *philo)
{
	ph_print(philo, SLEEPING);
	drop_forks(philo);
	ph_usleep(philo->data->t_sleep);
}

void	think_cycle(t_philo *philo)
{
	ph_print(philo, THINKING);
}

void	*cycle(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!exit_flag_check(philo))
	{
		eat_cycle(philo);
		sleep_cycle(philo);
		think_cycle(philo);
	}
	return (NULL);
}
