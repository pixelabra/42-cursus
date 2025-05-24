/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/24 18:06:34 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {}

Base	*generate(void) {
	int t  = rand();

	if (t % 3 == 0) {
		return (new A());
	} else if (t % 3 == 1) {
		return (new B());
	} else if (t % 3 == 2) {
		return (new C());
	}
	return (NULL);
}

void	identify(Base *p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "p: type A" << std::endl; 
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "p: type B" << std::endl; 
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "p: type C" << std::endl; 
	}
}

void	identify(Base& p) {
	try {
		Base&	temp = dynamic_cast<A&>(p);
		std::cout << "p: type A" << std::endl;
		(void)temp;
	} catch (std::exception& e) {}
	try {
		Base&	temp = dynamic_cast<B&>(p);
		std::cout << "p: type B" << std::endl;
		(void)temp;
	} catch (std::exception& e) {}
	try {
		Base&	temp = dynamic_cast<C&>(p);
		std::cout << "p: type C" << std::endl;
		(void)temp;
	} catch (std::exception& e) {}
}
