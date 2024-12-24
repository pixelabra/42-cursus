/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:21:05 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/24 23:51:55 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() {
	type = "ak47";
}

Weapon::Weapon(std::string newtype) {
	type = newtype;
}

const std::string &Weapon::getType(void) {
	return (type);
}

void	Weapon::setType(std::string newtype) {
	type = newtype;
}
