/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:20 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 22:41:53 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_exit_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->exit_mtx);
	philo->data->exit_flag = 1;
	pthread_mutex_unlock(&philo->data->exit_mtx);
}

int	calculate_death(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->time_mtx);
	if (get_time() - philo->t_lastmeal >= (size_t)philo->data->t_death)
	{
		pthread_mutex_unlock(&philo->data->time_mtx);
		set_exit_flag(philo);
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%lu\t"RED BOLD"%d died\n"RESET,
			get_time() - philo->data->t_genesis, philo->index);
		pthread_mutex_unlock(&philo->data->print_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->time_mtx);
	return (0);
}

int	calculate_meals(t_philo *philos)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < philos->data->nbr_philos)
	{
		philo = &philos[i];
		pthread_mutex_lock(&philo->data->meals_mtx);
		if (philo->ate < philo->data->nbr_meals)
		{
			pthread_mutex_unlock(&philo->data->meals_mtx);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meals_mtx);
	}
	set_exit_flag(philo);
	return (1);
}

void	*overseer(void *philosophers)
{
	t_philo *philos;
	t_philo *philo;
	int		i;

	philos = (t_philo *)philosophers;
	i = -1;
	while (1)
	{
		philo = &philos[++i];
		if (calculate_death(philo))
			break ;
		if (philo->data->nbr_meals != -1 && calculate_meals(philos))
			break ;
		if (i == philo->data->nbr_philos - 1)
			i = -1;
	}
	return (NULL);
}
