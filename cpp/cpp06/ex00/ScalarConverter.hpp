/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:04:10 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/14 20:16:19 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#ifndef SCALARCONVERTER_HPP
	# define SCALARCONVERTER_HPP

	# include <iostream>
	# include <cstdlib>
	# include <climits>
	# include <cmath>

	class ScalarConverter
	{
		private:
			ScalarConverter();
			ScalarConverter(const ScalarConverter& other);
			ScalarConverter& operator=(const ScalarConverter& other);
		public:
			static void	convert(const std::string& literal);
			~ScalarConverter();
	};

	void	parseInput(const std::string& literal);

	#endif