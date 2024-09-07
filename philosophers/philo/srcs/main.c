/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:49:48 by agodeanu          #+#    #+#             */
/*   Updated: 2024/09/07 21:52:19 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*flags;

	if (init(data, philos, forks, flags))
		return (1);
	
	return (0);
}
