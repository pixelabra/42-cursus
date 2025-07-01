/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:51:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/01 18:51:02 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(): N(0) {}

Span::Span(unsigned int _N): N(_N) {}

Span::Span(const Span& other): container(other.container), N(other.N) {}

Span&	Span::operator=(const Span& other) {
	if (this != &other) {
		N = other.N;
		container = other.container;
	}
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int number) {
	if (container.size() >= N) {
		throw std::out_of_range("Span is FULLL!!");
	}
	container.push_back(number);
	std::cout << "Added: Index [" << container.size() - 1 << "]: "
		<< RED BOLD << &container[container.size() - 1] << RESET;
	std::cout << " content: " << container[container.size() - 1] << std::endl;
}

int		Span::longestSpan() {
	if (container.size() <= 1) {
		throw std::invalid_argument("Span has one element only / Span has no elements");
	}
	int	longSpan = *std::max_element(container.begin(), container.end())
	- *std::min_element(container.begin(), container.end());
	std::cout << BOLD << "Longest span: " << RED << longSpan << RESET << std::endl;
	return (longSpan);
}

int		Span::shortestSpan() {
	if (container.size() <= 1) {
		throw std::invalid_argument("Span has one element only / Span has no elements");
	}
	std::vector<int>	temp(container);
	std::sort(temp.begin(), temp.end());
	int	shortSpan = *std::max_element(container.begin(), container.end())
	- *std::min_element(container.begin(), container.end());
	for (size_t i = 1; i < temp.size(); ++i) {
		int	delta = (temp[i] - temp[i - 1]);
		if (delta < shortSpan) {
			shortSpan = delta;
		}
	}
	std::cout << BOLD << "Shortest span: " << RED << shortSpan << RESET << std::endl;
	return (shortSpan);
}

void	Span::printVector() {
	printContainer(this->container);
}

void	Span::fillSpan(size_t nFill, size_t nDiv) {
	for (size_t i = 0; i < nFill; i++) {
		this->addNumber(rand() % nDiv + 1);
	}
}
