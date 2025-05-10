/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:08:22 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/07 19:07:31 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {(void)other;}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return (*this); }

ScalarConverter::~ScalarConverter() {}

void	ScalarConverter::convert(const std::string& input)
{
	parsingInput(input);
	
}

size_t	charCounter(const std::string& input, const char& c)
{
	size_t	counter = 0;
	size_t	start = 0;
	size_t	end;

	while (1) {
		end = input.find(c, start);
		if (end == input.npos) {
			break ;
		}
		start = end + 1;
		counter++;
	}
	return (counter);
}

void	parsingInput(const std::string& input)
{
	if (input.size() == 1 && !std::isdigit(input[0])) {
		char c = input[0];
		std::cout << c << std::endl;
	} else if (input.size() != 1) {
		
	}
	size_t	counter = charCounter(input, '-');
	// if (counter > 2) 
	// if (charCounter(input, '.') > 1) {
	// 	std::cerr << "Error: input cannot have multiple '.'" << std::endl;
	// }
	// if (charCounter(input, '-') > 1 || ) {
	// 	std::cerr << "Error: input cannot have multiple '.'" << std::endl;
	// }
	// if (charCounter(input, 'f') > 1) {
	// 	std::cerr << "Error: input cannot have multiple '.'" << std::endl;
	// }
	
	std::cout << counter << std::endl;
}
