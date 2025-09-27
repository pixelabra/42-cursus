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

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& fileName) {
	this->fileName = fileName;
	fillRegistry();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): registry(other.registry) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		registry = other.registry;
	}
	return *this;
}

float	BitcoinExchange::getValue(const std::string& date) const {
	// std::map<std::string, float>::iterator it = this->registry.find(date);
	// if (it != this->registry.end())
	// 	return it->second;
	// return (-1);
	(void)date;
	return (-1);
}

void	BitcoinExchange::fillRegistry() {
	std::ifstream	db;
	std::string		line;
	std::string		date;
	std::string		value;

	db.open("data.csv");
	if(!db.is_open())
		throw std::exception();
	if (!getline(db,line) || line != "date,exchange_rate") {
		db.close();
		throw std::exception();
	}
	size_t count = 1;
	while(getline(db, line)) {
		count++;
		size_t comma = line.find(",", 0);
		if (comma == line.npos) {
			std::cerr << "Line [" << count << "]: " << WR_DB_ROW_FORMAT << std::endl;
			continue ;
		}
		date = line.substr(0, comma);
		value = line.substr(comma + 1, static_cast<size_t>(line.length()));
		if (!isValidDate(date) || !isValidValue(value)) {
			std::cerr << "Line [" << count << "]: " << WR_DB_ROW_FORMAT << std::endl;
			continue ;
		}
		this->registry[date] = std::atof(value.c_str());
	}
	db.close();
}

bool	BitcoinExchange::isValidDate(const std::string& date) const {
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

bool	BitcoinExchange::isValidValue(const std::string& value) const {
	char	*end = NULL;

	std::strtof(value.c_str(), &end);
	if ((!isdigit(value[0]) && value[0] != '.') || end[0])
		return false;
	return true;
}

float	BitcoinExchange::findClosestPrice(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = this->registry.upper_bound(date);
	if (it != this->registry.begin()) {
		it--;
	}
	return (it->second);
	// return ((registry.end() - 1)->second);
}

void	BitcoinExchange::evaluateInput() const {
	std::ifstream	file;
	std::string		line;
	std::string		date;
	std::string		tknQstr;
	float			tknQ;
	float			price;

	file.open(this->fileName);
	if (!file.is_open())
		throw std::exception();
	if (!getline(file,line) || line != "date | value") {
		file.close();
		throw std::exception();
	}
	size_t count = 1;
	while(getline(file, line)) {
		count++;
		size_t pipe = line.find(" | ", 0);
		if (pipe == line.npos) {
			std::cerr << "Line [" << count << "]: " << WR_DB_ROW_FORMAT << std::endl;
			continue ;
		}
		date = line.substr(0, pipe);
		tknQstr = line.substr(pipe + 3, static_cast<size_t>(line.length()));
		if (!isValidDate(date) || !isValidValue(tknQstr)) {
			std::cerr << "Line [" << count << "]: " << WR_INF_ROW_FORMAT << std::endl;
			continue ;
		}
		tknQ = std::atof(tknQstr.c_str());
		if (tknQ <= 0 || tknQ >= 1000) {
			std::cerr << "Line [" << count << "]: " << "Token quantity required range [0, 1000]" << std::endl;
			continue ;
		}
		price = findClosestPrice(date);
		std::cout << date << " => " << price << " * " << tknQ << " = " << static_cast<double>(price * tknQ) << std::endl;
	}
}
