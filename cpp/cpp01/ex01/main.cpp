/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:51:56 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 17:01:52 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main()
{
	{
		Zombie	*horde;
		int		N;

		N = 10;
		horde = zombieHorde(N, "Zombie");
		horde[6].setName("Evil Zombie");
		for (int i = 0; i < N; i++)
			horde[i].announce();
		delete[] horde;
	}
	return (0);
}
