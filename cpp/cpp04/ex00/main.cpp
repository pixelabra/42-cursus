/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:32:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/04 16:52:44 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main()
{
	{
		std::cout << BLUE BOLD << "Scope 1\n" << RESET;
		const Animal	*meta = new Animal();
		const Animal	*j = new Dog();
		const Animal	*i = new Cat();
		
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
		std::cout << BLUE BOLD << "Scope 2\n" << RESET;
		const WrongAnimal	*k = new WrongCat();
		std::cout << k->getType() << " " << std::endl;
		k->makeSound();
		delete k;
	}
	std::cout << std::endl;
	{
		std::cout << BLUE BOLD << "Scope 3\n" << RESET;
		std::cout <<  RED BOLD << "Copy constructor and assignment overload test for ANIMAL:\n\n" << RESET;
		Animal	*plushie = new Animal("plushie");
		Animal	woofy(*plushie);
		Animal	splooshy("splooshy");

		woofy = splooshy;
		std::cout << "GetType and makeSound animal testing:\n";
		std::cout << "Plushie type is: " << plushie->getType() << std::endl;
		std::cout << "Woofy type is: " << woofy.getType() << std::endl;

		std::cout << "Sound of splooshy: ";
		splooshy.makeSound();
		std::cout << std::endl;

		std::cout << RED BOLD << "Copy constructor, getType and makeSound test for CAT:\n" << RESET;
		Cat		swooshy;
		Cat		wannabe_swooshy(swooshy);
		Cat		swooshswoosh;

		std::cout << "Type of wannabe_swooshy is: " << wannabe_swooshy.getType() << std::endl;
		std::cout << "Sound of wannabe_swooshy is: ";
		wannabe_swooshy.makeSound();
		std::cout << "\n";

		swooshy.setType("swooshy");
		swooshswoosh = swooshy;
		std::cout << "Type of wooshwoosh is: " << swooshswoosh.getType() << std::endl;

		std::cout << RED BOLD << "Copy constructor, getType and makeSound test for DOG:\n" << RESET;
		Dog		wooshy;
		Dog		wannabe_wooshy(wooshy);
		Dog		wooshwoosh;
		
		std::cout << "Type of wannabe_wooshy is: " << wannabe_wooshy.getType() << std::endl;
		std::cout << "Sound of wannabe_wooshy is: ";
		wannabe_wooshy.makeSound();
		std::cout << "\n";
		
		wooshy.setType("wooshy");
		wooshwoosh = wooshy;
		std::cout << "Type of wooshwoosh is: " << wooshwoosh.getType() << std::endl;
		
		std::cout << RED BOLD << "Self-assignment:\n" << RESET;
		wooshy = wooshy;
		swooshy = swooshy;
		splooshy = splooshy;
		
		std::cout << RED BOLD << "Slicing:\n" << RESET;
		Animal	sliced = Dog();
		sliced.makeSound();
		std::cout << "\n";
		
		std::cout << RED BOLD << "Apocalyptic Event:\n" << RESET;
		delete plushie;
	}
	return (0);
}
