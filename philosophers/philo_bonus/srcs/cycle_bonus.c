/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:50:24 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/13 01:25:377 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int		exit_flag_check(t_philo *philo)
{
	int	exit_return;

	sem_wait(philo->data->exit_sem);
	exit_return = philo->data->exit_flag;
	sem_post(philo->data->exit_sem);
	return (exit_return);
}

void	ph_print(t_philo *philo, int print_flag)
{
	if (!exit_flag_check(philo))
	{
		sem_wait(philo->data->print_sem);
		if (print_flag == EATING && !exit_flag_check(philo))
			printf("%lu\t"GREEN BOLD"%d is eating\n"RESET,
				get_time() - philo->data->t_genesis, philo->index);
		else if (print_flag == SLEEPING && !exit_flag_check(philo))
			printf("%lu\t"BLUE"%d is sleeping\n"RESET,
				get_time() - philo->data->t_genesis, philo->index);
		else if (print_flag == THINKING && !exit_flag_check(philo))
			printf("%lu\t"MAGENTA"%d is thinking\n"RESET,
				get_time() - philo->data->t_genesis, philo->index);
		else if (print_flag == TAKE_FORK && !exit_flag_check(philo))
			printf("%lu\t"YELLOW"%d has taken a fork\n"RESET,
				get_time() - philo->data->t_genesis, philo->index);
		sem_post(philo->data->print_sem);
	}
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
