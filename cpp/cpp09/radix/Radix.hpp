/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Radix.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:46:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/09 15:02:14 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_HPP
# define RADIX_HPP

# include <iostream>
# include <vector>
# include <algorithm>
# include <cstdlib>

# define RESET		"\x1b[0m"
# define BOLD		"\x1b[1m"
# define BLACK		"\x1b[40m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[37m"

template <typename T>
void	printContainer(const T& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << "Index [" << i << "]: "
			<< RED BOLD << &a[i] << RESET;
		std::cout << " content: " << a[i] << std::endl;
	}
}

template <typename T>
void	fillIt(T& a, size_t nFill, int range) {
	for (size_t i = 0; i < nFill; i++) {
		a.push_back(rand() % (2 * range + 1) - range);
	}
}

void				sortRadix(std::vector<int>& arr, unsigned int nBits, unsigned int r);
std::vector<int>&	radix(std::vector<int>& arr, unsigned int r);

#endif