/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:59:34 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/01 19:05:07 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <cstdlib>
# include <exception>
# include <vector>
# include <list>
# include <deque>
# include <algorithm>

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
void	printContainer(T& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << "Index [" << i << "]: "
			<< RED BOLD << &a[i] << RESET;
		std::cout << " content: " << a[i] << std::endl;
	}
}

template <typename T>
void	fillIt(T& a, size_t nFill, size_t nDiv) {
	for (size_t i = 0; i < nFill; i++) {
		a.push_back(rand() % nDiv);
	}
}

class Span {
	private:
		std::vector<int>	container;
		unsigned int		N;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void	addNumber(int number);
		int		shortestSpan();
		int		longestSpan();

		void	printVector();
		void	fillSpan(size_t nFill, size_t nDiv);

		template <typename T>
		void	fillSpanRange(T beginIt, T endIt) {
			if (container.size() + std::distance(beginIt, endIt) > N) {
					throw std::out_of_range("The range size is too big");
			}
			container.insert(container.end(), beginIt, endIt);
		};
};

#endif