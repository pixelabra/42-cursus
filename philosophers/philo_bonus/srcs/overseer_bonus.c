/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:23:59 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 18:07:16 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	set_exit_flag(t_philo *philo)
{
	sem_wait(philo->data->exit_sem);
	philo->data->exit_flag = 1;
	sem_post(philo->data->exit_sem);
}

int	calculate_death(t_philo *philo)
{
	int	i;

	i = -1;
	sem_wait(philo->data->time_sem);
	if (get_time() - philo->t_lastmeal >= (size_t)philo->data->t_death)
	{
		sem_post(philo->data->time_sem);
		sem_wait(philo->data->print_sem);
		if (!exit_flag_check(philo))
			printf("%lu\t"RED BOLD"%d died\n"RESET,
				get_time() - philo->data->t_genesis, philo->index);
		while (++i < philo->data->nbr_philos)
			sem_post(philo->data->death);
		// sem_post(philo->data->print_sem);
		return (1);
	}
	sem_post(philo->data->time_sem);
	return (0);
}

void	*death_checker(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	sem_wait(philo->data->death);
	sem_post(philo->data->full);
	sem_wait(philo->data->exit_sem);
	philo->data->exit_flag = 1;
	sem_post(philo->data->exit_sem);
	return (NULL);
}

void	*overseer(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		if (exit_flag_check(philo))
			break ;
		if (calculate_death(philo))
			break ;
	}
	return (NULL);
}
