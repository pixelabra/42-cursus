/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:58:11 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/15 00:58:16 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

void	Harl::debug(void) {
	std::cout << "I love having sweet treat when stuff stuff\n";
}

void	Harl::info(void) {
	std::cout << "Adding sweet treats is just amazing and we should all sweet treat ourselves.\n";
}

void	Harl::warning(void) {
	std::cout << "If you don't give me sweet treat, I'll get upset\n";
}

void	Harl::error(void) {
	std::cout << "No sweet treat: angry me!\n";
}

void	Harl::complain(std::string level)
{
	int			i;
	void		(Harl::*fn_ptrs[4])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string	complain_msg[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (i = 0; i < 4; i++)
		if (level == complain_msg[i])
			break ;
	switch (i)
	{
		case 0:
			(this->*fn_ptrs[0])();
		case 1:
			(this->*fn_ptrs[1])();
		case 2:
			(this->*fn_ptrs[2])();
		case 3:
			(this->*fn_ptrs[3])();
			break ;
		default:
			std::cout << "unknown message or whatever\n";
	}
}
