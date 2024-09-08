/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:50:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 18:19:52 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		exit_flag_check(t_philo *philo)
{
	int	exit_return;

	pthread_mutex_lock(&philo->data->exit_mtx);
	exit_return = philo->data->exit_flag;
	pthread_mutex_unlock(&philo->data->exit_mtx);
	return (exit_return);
}

void	ph_print(t_philo *philo, int print_flag)
{
	if (!exit_flag_check(philo))
	{
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%lu\t", get_time() - philo->data->t_genesis);
		printf("%d ", philo->index);
		if (print_flag == EATING)
			printf("is eating\n");
		else if (print_flag == SLEEPING)
			printf("is sleeping\n");
		else if (print_flag == THINKING)
			printf("is thinking\n");
		else if (print_flag == TAKE_FORK)
			printf("has taken a fork\n");
		else if (print_flag == DEATH)
			printf("died\n");
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
}

void	eat_cycle(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->ate == 0)
		ph_usleep(philo->data->t_eat / 2);
	pthread_mutex_lock(philo->r_fork);
	ph_print(philo, TAKE_FORK);
	pthread_mutex_lock(philo->l_fork);

	pthread_mutex_unlock();
}

void	sleep_cycle(t_philo *philo)
{

}

void	think_cycle(t_philo *philo)
{

}

void	*cycle(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	int i = 0;
	while (i < 5)
		printf("%d\n", i++);
	return (NULL);
}
