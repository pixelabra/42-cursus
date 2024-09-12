/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:52 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/13 01:30:47 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>

// Colours
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define BOLD		"\x1b[1m"
# define RESET		"\x1b[0m"

// Actions
# define EATING 	1
# define SLEEPING	2
# define THINKING	3
# define TAKE_FORK	4
# define DEATH		5

# define RIGHT_FLAG	1
# define LEFT_FLAG	2

// Structs
typedef struct s_data
{
	int				nbr_philos;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nbr_meals;
	int				exit_flag;
	size_t			t_genesis;
	sem_t			*forks;
	sem_t			*exit_sem;
	sem_t			*time_sem;
	sem_t			*meals_sem;
	sem_t			*print_sem;
	sem_t			*death;
	sem_t			*full;
}	t_data;

typedef struct s_philo
{
	int				index;
	int				ate;
	size_t			t_lastmeal;
	t_data			*data;
	pthread_t		monitoring;
	pthread_t		death_th;
}	t_philo;

// Memory Management
int		allocator(t_data *data, t_philo **philos);
int		sem_destroyer(t_data *data);
void	sem_unlinker(void);
void	sem_closer(t_data *data);

// Initialisation Functions
int		init_data(t_data *data, int ac, char **av);
int		init_semaphores(t_data *data);
int		init_philos(t_data *data, t_philo *philos);

// Input Validation & Parsing
int		ph_isdigit(char *av);
long	ph_atol(const char *str);
size_t	ph_strlen(const char *str);
int		input_checker(t_data *data, char **av);

// Process Management
int		process_creator(t_data *data, t_philo *philos);
void	cycle(t_philo *philo);
void	*overseer(void *philosophers);

// Cycle Functions
void	eat_cycle(t_philo *philos);
void	sleep_cycle(t_philo *philos);
void	think_cycle(t_philo *philos);

// Timing Functions
size_t	get_time(void);
void	ph_usleep(size_t t_ms);

// Print & Exit Management
int		exit_flag_check(t_philo *philo);
int		calculate_death(t_philo *philo);
int		calculate_meals(t_philo *philos);
void	ph_print(t_philo *philo, int print_flag);

#endif