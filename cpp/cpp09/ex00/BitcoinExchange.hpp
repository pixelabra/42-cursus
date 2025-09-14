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
# include <sstream>

class BitcoinExchange
{
	private:
		std::string	_date;
		float		_value;
	public:
		BitcoinExchange();
		BitcoinExchange(std::string date, float value);
		BitcoinExchange(const BitcoinExchange& src);
		~BitcoinExchange();
		BitcoinExchange& operator=(const BitcoinExchange& src);
		
		const std::string&	getDate() const;
		const float&		getValue() const;
		void		setDate(const std::string& date);
		void		setValue(const float& value);
		bool		isValidDate(const std::string& date);
		bool		isValidValue(const std::string& value);

};

void	readInput(char *fileName);
void	checkArguments();

#endif