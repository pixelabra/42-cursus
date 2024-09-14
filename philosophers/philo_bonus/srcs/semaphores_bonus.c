/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:21:37 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/14 17:22:23 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	sem_unlinker(void)
{
	sem_unlink("/full");
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/exit_sem");
	sem_unlink("/time_sem");
	sem_unlink("/meals_sem");
	sem_unlink("/print_sem");
}

void	sem_closer(t_data *data)
{
	sem_close(data->full);
	sem_close(data->death);
	sem_close(data->forks);
	sem_close(data->exit_sem);
	sem_close(data->time_sem);
	sem_close(data->meals_sem);
	sem_close(data->print_sem);
}

int	sem_destroyer(t_data *data)
{
	sem_closer(data);
	sem_unlinker();
	return (0);
}
