/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:51:56 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/02 17:17:21 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main()
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	str2 = "Alexandru Gabriel";
	std::string	*strPTR = &str;
	std::string	&strREF = str;

	std::cout << &str << std::endl;
	std::cout << strPTR << std::endl;
	std::cout << &strREF << std::endl;
	std::cout << std::endl;
	std::cout << str << std::endl;
	std::cout << *strPTR << std::endl;
	std::cout << strREF << std::endl;

	std::cout << std::endl;
	strPTR = &str2;
	std::cout << *strPTR << std::endl;
	strREF = str2;
	std::cout << str << std::endl;
	return (0);
}
