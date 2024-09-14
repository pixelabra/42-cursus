/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:15:36 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 17:18:24 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	exit_flag_check(t_philo *philo)
{
	int	exit_return;

	sem_wait(philo->data->exit_sem);
	exit_return = philo->data->exit_flag;
	sem_post(philo->data->exit_sem);
	return (exit_return);
}

void	eat_cycle(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->ate == 0)
		ph_usleep(philo->data->t_eat / 2);
	sem_wait(philo->data->forks);
	ph_print(philo, TAKE_FORK);
	sem_wait(philo->data->forks);
	ph_print(philo, TAKE_FORK);
	ph_print(philo, EATING);
	sem_wait(philo->data->time_sem);
	philo->t_lastmeal = get_time();
	sem_post(philo->data->time_sem);
	sem_wait(philo->data->meals_sem);
	philo->ate++;
	if (philo->data->nbr_meals != -1
		&& philo->ate == philo->data->nbr_meals)
		sem_post(philo->data->full);
	sem_post(philo->data->meals_sem);
	ph_usleep(philo->data->t_eat);
}

void	sleep_cycle(t_philo *philo)
{
	ph_print(philo, SLEEPING);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ph_usleep(philo->data->t_sleep);
}

void	think_cycle(t_philo *philo)
{
	ph_print(philo, THINKING);
}

void	cycle(t_philo *philo)
{
	while (!exit_flag_check(philo))
	{
		eat_cycle(philo);
		sleep_cycle(philo);
		think_cycle(philo);
	}
}
