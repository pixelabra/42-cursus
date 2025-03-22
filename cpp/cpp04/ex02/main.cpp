/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:32:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/22 17:26:44 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main()
{
	{
		const Animal		*j = new Dog();
		const Animal		*i = new Cat();

		std::cout << j->getType() << " " << std::endl;	
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		j->makeSound();
		delete i;
		delete j;
	}
	std::cout << std::endl;
	{
		int	N = 10;
		Animal	*herd[N];

		for (int i = 0; i < N; i++)
		{
			if (i < N / 2)
				herd[i] = new Cat();
			else
				herd[i] = new Dog();
		}
		for (int i = 0; i < N; i++)
			std::cout << herd[i]->getType() << std::endl;
		for (int i = 0; i < N; i++)
			delete herd[i];
	}
	{
		const Cat	appowo;
		const Cat	luna(appowo);

		std::cout << luna.getType() << std::endl;
		appowo.getIdeas();
	}
	{
	// 	Animal	forbidden;
		const Animal	*lunesytoonesy = new Cat();

		lunesytoonesy->makeSound();
		delete lunesytoonesy;
	}
	return (0);
}
