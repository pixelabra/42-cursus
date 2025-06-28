/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:37:47 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/28 17:29:21 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <chrono>
#include <map>

int main() {
	// srand(time(0));
	// auto roll = []() { return rand() % 6 + 1;};
	// std::list<int>	container;

	// container.push_back(roll());
	// const int	*pAddressOfOriginalItemZero = &(*container.begin());
	
	// std::chrono::duration<double>	durInsertTime(0);
	
	// do {
	// 	const int	*pAddressOfItemZero = &(*container.begin());
	
	// 	std::cout << "Contains " << container.size() << " elements, took " <<
	// 		std::chrono::duration_cast<std::chrono::microseconds>(durInsertTime).count() << "us\n";
	// 	for (const auto& i : container) {
	// 		const int *pAddressOfItemX  = &i;
	// 		int pItemOffset = pAddressOfItemX - pAddressOfItemZero;
	// 		int pItemOffsetOriginal = pAddressOfItemX - pAddressOfOriginalItemZero;
	// 		std::cout << "Offset from Original: " << pItemOffsetOriginal << " Offset from Zero: " << pItemOffset << " :      Content: " << i << "\n";
	// 	}
	// 	auto tp1 = std::chrono::high_resolution_clock::now();
	// 	container.push_back(roll());
	// 	auto tp2 = std::chrono::high_resolution_clock::now();
	// 	durInsertTime = (tp1 - tp2);
			
	// } while (getc(stdin));

	// std::map<std::string, int>	container;
	// container["one"] = 1;
	// container["two"] = 2;
	// container["three"] = 3;
	// container["four"] = 4;
	// container["five"] = 5;
	// container["six"] = 6;
	// container["seven"] = 7;

	// for (auto& i : container) {
	// 	std::cout << i.first << " = " << i.second << std::endl;
	// }
	return (0);
}
