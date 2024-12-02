/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:51:56 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 16:16:11 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main()
{
	{
		Zombie	zombie_default;
		Zombie	zombie_stack("Stack Zombie");
		Zombie	*zombie_heap;

		zombie_heap = newZombie("Heap Zombie");
		delete(zombie_heap);
	}
	std::cout << std::endl;
	{
		randomChump("Chump Zombie");
		Zombie	*zombie = newZombie("Heap Zombie");
		zombie->announce();
		zombie->announce();
		zombie->announce();
		delete(zombie);
	}
	return (0);
}
