/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:08:22 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/14 19:29:58 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return (*this); }

ScalarConverter::~ScalarConverter() {}

void	ScalarConverter::convert(const std::string& input) {
	parseInput(input);
}

void	convertChar(char c) {
	if (c < 32 || c == 127) {
		std::cout << "char: Non displayable." << std::endl;
	}
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void	convertInt(int number) {
	if ((number >= 0 && number < 32) || number == 127) {
		std::cout << "char: Non displayable" << std::endl;
	} else if (number < 0 || number > 127) {
		std::cout << "char: impossible" << std::endl;
	} else {
		std::cout << "char: '" << (char)number << "'" << std::endl;
	}
	std::cout << "int: " << number << std::endl;
	std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(number) << ".0" << std::endl;
}

void	convertFloat(float number) {
	if ((number >= 0 && number < 32) || number == 127) {
		std::cout << "char: Non displayable" << std::endl;
	} else if (number < 0 || number > 127) {
		std::cout << "char: impossible" << std::endl;
	} else {
		std::cout << "char: '" << (char)number << "'" << std::endl;
	}
	if (number > INT_MAX || number < INT_MIN) {
		std:: cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(number) << std::endl;
	}
	if (number == floorf(number)) {
		std::cout << "float: " << number << ".0f" << std::endl;
	} else {
		std::cout << "float: " << number << "f" << std::endl;
	}
	if (number == floorf(number)) {
		std::cout << "double: " << static_cast<double>(number) << ".0" << std::endl;
	} else {
		std::cout << "double: " << static_cast<double>(number) << std::endl;
	}
}

void	convertDouble(double number) {
	if ((number >= 0 && number < 32) || number == 127) {
		std::cout << "char: Non displayable" << std::endl;
	} else if (number < 0 || number > 127) {
		std::cout << "char: impossible" << std::endl;
	} else {
		std::cout << "char: '" << (char)number << "'" << std::endl;
	}
	if (number > INT_MAX || number < INT_MIN) {
		std:: cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(number) << std::endl;
	}
	if (number == floor(number)) {
		std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
	} else {
		std::cout << "float: " << static_cast<float>(number) << "f" << std::endl;
	}
	if (number == floor(number)) {
		std::cout << "double: " << number << ".0" << std::endl;
	} else {
		std::cout << "double: " << number << std::endl;
	}
}

void	detectType(const std::string& input, double& number) {
	if (input.length() == 1 && !std::isdigit(input[0])) {
		convertChar(input[0]);
	} else if (input.find('.', 0) != input.npos) {
		if (input.find('f', 0)) {
			convertFloat(atof(input.c_str()));
		} else {
			convertDouble(number);
		}
	} else if (number > INT_MAX || number < INT_MIN) {
		std::cerr << "Error: int displayed not nice." << std::endl;
	} else {
		convertInt(atoi(input.c_str()));
	}
}

void	checkInfNanf(const std::string& _input) {
	size_t	i, j;

	for (i = 0; i < _input.length(); i++) {
		if (!isspace(_input[i])) {
			break ;
		}
	}
	for (j = _input[_input.length() - 1]; j > 0; j--) {
		if (!isspace(_input[j])) {
			break ;
		}
	}
	std::string	input = _input.substr(i, j);
	if (input == "+inf" || input == "-inf" || input == "+inff" || input == "-inff") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (input == "+inf" || input == "-inf") {
			std::cout << "float: " << input << "f" << std::endl;
		} else {
			std::cout << "float: " << input << std::endl;
		}
		if (input == "+inf" || input == "-inf") {
			std::cout << "double: " << input << std::endl;
		} else if (input == "+inff") {
			std::cout << "double: " << "+inf" << std::endl;
		} else if (input == "-inff") {
			std::cout << "double: " << "-inf" << std::endl;	
		}
		exit(0);
	}
	if (input == "nan" || input == "nanf") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << "nanf" << std::endl;
		std::cout << "double: " << "nan" << std::endl;
		exit(0);
	}
}

void	parseInput(const std::string& input) {
	char	*endPtr = NULL;
	double	number = strtod(input.c_str(), &endPtr);

	checkInfNanf(input);
	if ((input.length() > 0 && (!*endPtr || (*endPtr && (input.find('.', 0) != input.npos)
		&& (!*(endPtr + 1)) && (*endPtr == 'f'))))
		|| (input.length() == 1 && !std::isdigit(input[0]))) {
			detectType(input, number);
	} else {
		std::cerr << "invalid literal." << std::endl;
	}
}
