/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:16:10 by agodeanu          #+#    #+#             */
/*   Updated: 2025/09/14 15:57:31 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>

BitcoinExchange::BitcoinExchange(): _date(""), _value(0.0f) {}

BitcoinExchange::BitcoinExchange(std::string date, float value): _date(date), _value(value) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): _date(other._date), _value(other._value) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_date = other._date;
		_value = other._value;
	}
	return *this;
}

const std::string& BitcoinExchange::getDate() const {
	return _date;
}

const float&	BitcoinExchange::getValue() const {
	return _value;
}

void	BitcoinExchange::setDate(const std::string& date) {
	_date = date;
}

void	BitcoinExchange::setValue(const float& value) {
	_value = value;
}

bool	BitcoinExchange::isValidDate(const std::string& date) {
	std::stringstream	ss(date);
	int					year, month, day;

	if (date.length() != 10)
		return false;
	if (ss >> year && ss.get() == '-' && ss >> month && ss.get() == '-' && ss >> day) {
		if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
			return false;
		if ((month == 4 || month == 6 || month == 9 || month == 11) && month > 30)
			return false;
		if (month == 2) {
			if (year % 4 == 0 && day > 29)
				return false;
			else if (year % 4 != 0 && day > 28)
				return false;
		}
	}
	else
		return false;
	if (ss.get() != -1)
		return false;
	return true;
}

bool	BitcoinExchange::isValidValue(const std::string& value) {
	std::stringstream	ss1(value);
	std::stringstream	ss2(value);
	int					val1;
	float				val2;

	ss1 >> val1;
	if (ss1.get() != -1)
		std::cout << "This is not an int" << std::endl;
	ss2 >> val2;
	std::cout << val2 << std::endl;
	// if (ss2.get() != -1)
	// 	std::cout << "This is not a float" << std::endl;
	return true;
}
