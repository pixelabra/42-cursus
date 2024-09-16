/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:40:26 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 16:44:03 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_print(t_philo *philo, int print_flag)
{
	if (!exit_flag_check(philo))
	{
		pthread_mutex_lock(&philo->data->print_mtx);
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
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
}
