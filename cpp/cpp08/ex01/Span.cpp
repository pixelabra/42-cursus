/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:51:03 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/28 21:08:12 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(): N(0) {}

Span::Span(unsigned int _N): N(_N) {}

Span::Span(const Span& other): N(other.N) {

}

Span&	Span::operator=(const Span& other) {
	if (this != &other) {
		
	}
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int number) {
	if (container.size() >= N) {
		throw std::out_of_range("Span is FULLL!!");
	}
	container.push_back(number);
}
