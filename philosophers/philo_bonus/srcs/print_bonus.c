/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:17:43 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 17:18:19 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
