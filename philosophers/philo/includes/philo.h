/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:52 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/07 22:17:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define BOLD    "\x1b[1m"
# define RESET   "\x1b[0m"

typedef struct s_data
{
	int				nbr_philos;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nbr_meals;
	size_t			t_genesis;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
	pthread_mutex_t	time;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				ate;
	size_t			t_lastmeal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				*r_flag;
	int				*l_flag;
}	t_philo;

#endif