/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:47:20 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/14 23:44:55 by agodeanu         ###   ########.fr       */
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
	void		(Harl::*debug_ptr)() = &Harl::debug;
	void		(Harl::*info_ptr)() = &Harl::info;
	void		(Harl::*warning_ptr)() = &Harl::warning;
	void		(Harl::*error_ptr)() = &Harl::error;
	void		(Harl::*ptr_func[4])() = {debug_ptr, info_ptr, warning_ptr, error_ptr};
	std::string	complain_msg[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
		
	for (int i = 0; i < 4; i++)
	{
		if (level == complain_msg[i])
		{
			(this->*ptr_func[i])();
			return ;
		}
	}
	std::cout << "Unknown complaint message. Do better.\n";
}
