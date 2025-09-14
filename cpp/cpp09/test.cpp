/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:36:31 by agodeanu          #+#    #+#             */
/*   Updated: 2025/09/14 14:35:34 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>

// int main() {
// 	std::string str = "123.456www";
// 	std::stringstream iss(str);
// 	float num;

// 	if (iss >> num) {
// 		std::cout << num << std::endl;
// 		return 0;
// 	} else {
// 		return 1;
// 	}
// }

int	main() {
	std::string input = "1*12-12-2023";
	std::stringstream	ss(input);
	int					day, month, year;

	ss >> day;
	std::cout << day << std::endl;
	return (0);
}
