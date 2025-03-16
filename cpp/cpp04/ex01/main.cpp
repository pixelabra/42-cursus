/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:32:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/15 21:06:59 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main()
{
	// {
	// 	const Animal		*meta = new Animal();
	// 	const Animal		*j = new Dog();
	// 	const Animal		*i = new Cat();

	// 	std::cout << j->getType() << " " << std::endl;	
	// 	std::cout << i->getType() << " " << std::endl;
	// 	i->makeSound();
	// 	j->makeSound();
	// 	meta->makeSound();
	// 	delete meta;
	// 	delete i;
	// 	delete j;
	// }
	// std::cout << std::endl;
	// {
	// 	const WrongAnimal	*k = new WrongCat();
	// 	std::cout << k->getType() << " " << std::endl;
	// 	k->makeSound();
	// 	delete k;
	// }
	// {
	// 	int	N = 3;
	// 	Animal	*herd[N];

	// 	for (int i = 0; i < N; i++)
	// 	{
	// 		if (i < N / 2)
	// 			herd[i] = new Cat();
	// 		else
	// 			herd[i] = new Dog();
	// 	}
	// 	for (int i = 0; i < N; i++)
	// 		delete herd[i];
	// }
	{
		const Cat	luna;
		const Cat	mochi(luna);
		const Dog	appowo;

		std::cout << mochi.getType() << std::endl;
	}
	return (0);
}
