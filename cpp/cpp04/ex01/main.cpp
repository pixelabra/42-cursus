/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:32:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/22 17:19:07 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main()
{
	{
		const Animal		*meta = new Animal();
		const Animal		*j = new Dog();
		const Animal		*i = new Cat();

		std::cout << j->getType() << " " << std::endl;	
		std::cout << i->getType() << " " << std::endl;
		i->makeSound();
		j->makeSound();
		meta->makeSound();
		delete meta;
		delete i;
		delete j;
	}
	std::cout << std::endl;
	{
		const WrongAnimal	*k = new WrongCat();
		std::cout << k->getType() << " " << std::endl;
		k->makeSound();
		delete k;
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
	std::cout << std::endl;
	{
		Cat	lunesy;
		Cat	apowinu;

		lunesy.setIdea(0, "ugh");
		lunesy.setIdea(1, "this one again");
		apowinu = lunesy;
		apowinu.setIdea(0, "who are you?");
		apowinu.getIdeas();
		lunesy.getIdeas();
	}
	std::cout << std::endl;
	{
		const Cat	appowo;
		const Cat	luna(appowo);

		std::cout << luna.getType() << std::endl;
		appowo.getIdeas();
	}
	return (0);
}
