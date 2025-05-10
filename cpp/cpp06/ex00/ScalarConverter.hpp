/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:04:10 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/07 18:38:12 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#ifndef SCALARCONVERTER_HPP
	# define SCALARCONVERTER_HPP

	# include <iostream>
	# include <limits>

	class ScalarConverter
	{
		private:
			ScalarConverter();
			ScalarConverter(const ScalarConverter& other);
			ScalarConverter& operator=(const ScalarConverter& other);
			~ScalarConverter();
		public:
			static void	convert(const std::string& literal);
	};

	void	parsingInput(const std::string& literal);

	#endif