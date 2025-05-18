/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/18 20:31:07 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base() {}

Base	*generate(void) {
	srand(time(0));
	if (rand() % 3 == 0) {
		return (new A());
	} else if (rand() % 3 == 1) {
		return (new B());
	} else if (rand() % 3 == 2) {
		return (new C());
	}
}
