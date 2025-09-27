/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:14:42 by agodeanu          #+#    #+#             */
/*   Updated: 2025/09/14 15:39:00 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <cstdlib>
# include <exception>

# define WR_DB_FILE			"Database non-existent"
# define WR_DB_ROW_FORMAT	"Database input row required format: <yyyy-mm-dd>,<int/float>"
# define WR_INF_ROW_FORMAT	"Database input row required format: <yyyy-mm-dd> | <int/float>"

class BitcoinExchange
{
	private:
		std::map<std::string, float>	registry;
		std::string						fileName;

		BitcoinExchange();
	public:
		BitcoinExchange(const std::string& fileName);
		BitcoinExchange(const BitcoinExchange& src);
		~BitcoinExchange();
		BitcoinExchange& operator=(const BitcoinExchange& src);
		
		float			getValue(const std::string& date) const;
		void			fillRegistry();
		bool			isValidDate(const std::string& date) const;
		bool			isValidValue(const std::string& value)const;
		void			evaluateInput() const;
		float			findClosestPrice(const std::string& date) const;
};

#endif