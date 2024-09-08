/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:50:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 16:40:16 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_print(t_philo *philo)
{
	
}

void	eat_cycle(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->ate == 0)
		ph_usleep(philo->data->t_eat / 2);
	pthread_mutex_lock(philo->r_fork);
	ph_print();
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
