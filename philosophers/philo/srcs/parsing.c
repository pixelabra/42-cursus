/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:04:57 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/08 14:56:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ph_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ph_isdigit(char *av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (!(av[i] >= '0' && av[i] <= '9'))
			return (0);
	return (1);
}

long	ph_atol(const char *str)
{
	int			i;
	long		sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((result == 922337203685477580
				&& str[i] > '7') || (result > 922337203685477580))
			return (-1 * (sign != -1));
		result = (result * 10) + (str[i++] - '0');
	}
	return ((result * sign));
}

int	input_checker(t_data *data, char **av)
{
	int		i;
	long	nbr;

	i = 0;
	while (av[++i])
	{
		if (!ph_isdigit(av[i]))
			return (1);
		nbr = ph_atol(av[i]);
		if (ph_strlen(av[i]) > 10 || nbr > 2147483647)
			return (1);
		if (i == 1)
			data->nbr_philos = nbr;
		else if (i == 2)
			data->t_death = nbr;
		else if (i == 3)
			data->t_eat = nbr;
		else if (i == 4)
			data->t_sleep = nbr;
		else if (i == 5)
			data->nbr_meals = nbr;
	}
	if (i == 5)
		data->nbr_meals = -1;
	return (0);
}
