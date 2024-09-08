/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:26:34 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 21:16:13 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	r_fork_retrieval(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (*philo->r_flag == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	*philo->r_flag = 1;
	pthread_mutex_unlock(philo->r_fork);
	ph_print(philo, TAKE_FORK);
	return (1);
}

int	l_fork_retrieval(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (*philo->l_flag == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	*philo->l_flag = 1;
	pthread_mutex_unlock(philo->l_fork);
	ph_print(philo, TAKE_FORK);
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	*philo->l_flag = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*philo->r_flag = 0;
	pthread_mutex_unlock(philo->r_fork);
}

void	get_forks(t_philo *philo)
{
	int	fork_flag;

	fork_flag = 0;
	while (!exit_flag_check(philo) && fork_flag == 0)
	{
		if (fork_flag == 0 && r_fork_retrieval(philo))
			fork_flag = RIGHT_FLAG;
		if (fork_flag == 0 && l_fork_retrieval(philo))
			fork_flag = LEFT_FLAG;
	}
	while (!exit_flag_check(philo))
	{
		if (fork_flag == RIGHT_FLAG)
		{
			if (l_fork_retrieval(philo))
				break ;
		}
		else if (fork_flag == LEFT_FLAG)
		{
			if (r_fork_retrieval(philo))
				break ;
		}
		usleep(100);
	}
}
