/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:47:49 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 01:12:8 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	init_data(t_data *data, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || input_checker(data, av))
	{
		printf(RED BOLD"Invalid input!\n"CYAN
			"./philo_bonus <nbr_philos> <t_death> "
			"<t_eat> <t_sleep> <nbr_meals>\n"
			YELLOW"All inputs must be positive integers.\n"RESET);
		return (1);
	}
	data->t_genesis = get_time();
	data->exit_flag = 0;
	return (0);
}

int	init_semaphores(t_data *data)
{
	sem_unlinker();
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nbr_philos);
	data->exit_sem = sem_open("/exit_sem", O_CREAT | O_EXCL, 0644, 1);
	data->time_sem = sem_open("/time_sem", O_CREAT | O_EXCL, 0644, 1);
	data->meals_sem = sem_open("/meals_sem", O_CREAT | O_EXCL, 0644, 1);
	data->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	data->full = sem_open("/full", O_CREAT | O_EXCL, 0644, 0);
	return (0);
}

int	init_philos(t_data *data, t_philo *philos)
{
	int		i;
	t_philo	*temp_philo;

	i = -1;
	while (++i < data->nbr_philos)
	{
		temp_philo = &philos[i];
		temp_philo->index = i + 1;
		temp_philo->ate = 0;
		temp_philo->t_lastmeal = get_time();
		temp_philo->data = data;
	}
	return (0);
}
