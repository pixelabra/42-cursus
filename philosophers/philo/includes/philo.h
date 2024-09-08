/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:52 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 19:18:57 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define BOLD		"\x1b[1m"
# define RESET		"\x1b[0m"

# define EATING 	1
# define SLEEPING	2
# define THINKING	3
# define TAKE_FORK	4
# define DEATH		5

# define RIGHT_FLAG	1
# define LEFT_FLAG	2

typedef struct s_data
{
	int				nbr_philos;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nbr_meals;
	int				exit_flag;
	size_t			t_genesis;
	pthread_mutex_t	exit_mtx;
	pthread_mutex_t	meals_mtx;
	pthread_mutex_t	time_mtx;
	pthread_mutex_t	print_mtx;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				ate;
	size_t			t_lastmeal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				*l_flag;
	int				*r_flag;
}	t_philo;

int		allocator(t_data *data, t_philo **philos, pthread_mutex_t **forks, int **flags);
void	free_all(t_philo *philos, pthread_mutex_t *forks, int *flags);
int		mtx_destroyer(t_data *data, pthread_mutex_t *forks);
int		init_data(t_data *data, int ac, char **av);
int		init_mtx(t_data *data, pthread_mutex_t *forks);
int		init_flags(t_data *data, int *flags);
int		init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks, int *flags);
int		ph_isdigit(char *av);
int		thread_creator(t_data *data, t_philo *philos);
long	ph_atol(const char *str);
int		input_checker(t_data *data, char **av);
void	ph_usleep(size_t t_ms);
void	*cycle(void *philosopher);
void	eat_cycle(t_philo *philos);
void	sleep_cycle(t_philo *philos);
void	think_cycle(t_philo *philos);
size_t	ph_strlen(const char *str);
size_t	get_time(void);
int		exit_flag_check(t_philo *philo);
void	ph_print(t_philo *philo, int print_flag);

#endif