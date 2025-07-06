/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:20:10 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/06 18:22:37 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
	{
		MutantStack<int> mstack;
	
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
	}
	std::cout << BLUE BOLD << "INTERLUDE" << RESET << std::endl;
	{
		srand(time(0));
		size_t	size = 10;
		MutantStack<float>	mstack;
	
		for (size_t i = 0; i < size; i++) {
			mstack.push(rand() % 100);
		}
		printStack(mstack);

		std::cout << "mstack.end(): " << RED BOLD << *(mstack.end() - 1) <<  RESET << std::endl;
		std::cout << "mstack.begin(): " << RED BOLD << *mstack.begin() <<  RESET << std::endl;
		std::cout << "mstack.rbegin(): " << RED BOLD << *(mstack.rbegin()) <<  RESET << std::endl;
		std::cout << "mstack.rend(): " << RED BOLD << *(mstack.rend() - 1) <<  RESET << std::endl;

		std::cout << MAGENTA BOLD << "CONST SITUATION" << RESET << std::endl;

		std::cout << "mstack.end(): " << RED BOLD << *static_cast<MutantStack<float>::const_iterator>(mstack.end() - 1) <<  RESET << std::endl;
		std::cout << "mstack.begin(): " << RED BOLD << *static_cast<MutantStack<float>::const_iterator>(mstack.begin()) <<  RESET << std::endl;
		std::cout << "mstack.rbegin(): " << RED BOLD << *static_cast<MutantStack<float>::const_reverse_iterator>(mstack.rbegin()) <<  RESET << std::endl;
		std::cout << "mstack.rend(): " << RED BOLD << *static_cast<MutantStack<float>::const_reverse_iterator>(mstack.rend() - 1) <<  RESET << std::endl;
	}
	return (0);
}
