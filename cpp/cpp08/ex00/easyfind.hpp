/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:59:34 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/08 13:43:39 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <cstdlib>
# include <exception>
# include <algorithm>
# include <vector>
# include <deque>

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
void	fillIt(T& a, size_t N) {
	for (size_t i = 0; i < N; i++) {
		a.push_back(rand() % 6);
	}
}

template <typename T>
void	printContainer(const T& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << "Index [" << i << "]: "
			<< RED BOLD << &a[i] << RESET;
		std::cout << " content: " << a[i] << std::endl;
	}
}

template <typename T>
int	*easyfind(T& a, int b) {
	typename T::iterator it = std::find(a.begin(), a.end(), b);

	if (it != a.end()) {
		std::cout << "WE FOUND IT: " << MAGENTA BOLD
				<< &(*it) << RESET << " content: " << *it << std::endl;
		return (&(*it));
	}
	throw (std::invalid_argument("We were not able to find the parameter."));
}

template <typename T>
const int	*easyfind(const T& a, int b) {
	typename T::const_iterator it = std::find(a.begin(), a.end(), b);

	if (it != a.end()) {
		std::cout << "WE FOUND IT: " << MAGENTA BOLD
				<< &(*it) << RESET << " content: " << *it << std::endl;
		return (&(*it));
	}
	throw (std::invalid_argument("We were not able to find the parameter."));
}

#endif