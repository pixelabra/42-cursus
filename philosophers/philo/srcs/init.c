/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:47:49 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 20:37:11 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	mtx_destroyer(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&data->exit_mtx);
	pthread_mutex_destroy(&data->meals_mtx);
	pthread_mutex_destroy(&data->time_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	i = 0;
	while (i < data->nbr_philos)
		pthread_mutex_destroy(&forks[i++]);
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	if ((ac != 5 && ac != 6) || input_checker(data, av))
	{
		printf(RED BOLD"Invalid input!\n"
			CYAN"./philo <nbr_philos> <t_death> <t_eat> <t_sleep> <nbr_meals>\n"
			YELLOW"All inputs must be integers.\n"RESET);
		return (1);
	}
	data->t_genesis = get_time();
	data->exit_flag = 0;
	return (0);
}

int	init_mtx(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (pthread_mutex_init(&data->exit_mtx, NULL))
		return (mtx_destroyer(data, forks));
	if (pthread_mutex_init(&data->meals_mtx, NULL))
		return (mtx_destroyer(data, forks));
	if (pthread_mutex_init(&data->time_mtx, NULL))
		return (mtx_destroyer(data, forks));
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (mtx_destroyer(data, forks));
	i = 0;
	while (i < data->nbr_philos)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (mtx_destroyer(data, forks));
	return (0);
}

int	init_flags(t_data *data, int *flags)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
		flags[i++] = 0;
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks, int *flags)
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
		if (i == 0)
		{
			temp_philo->l_fork = &forks[data->nbr_philos - 1];
			temp_philo->l_flag = &flags[data->nbr_philos - 1];
		}
		else
		{
			temp_philo->l_fork = &forks[i - 1];
			temp_philo->l_flag = &flags[i - 1];
		}
		temp_philo->r_fork = &forks[i];
		temp_philo->r_flag = &flags[i];
		printf("Philo ID %d\n", i);
		printf("Data %p\n", temp_philo->data);
		printf("Left fork and flag %p %p\n", temp_philo->l_fork, temp_philo->l_flag);
		printf("Right fork and flag %p %p\n\n", temp_philo->r_fork, temp_philo->r_flag);
	}
	return (0);
}

