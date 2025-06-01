/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:26:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/06/01 18:30:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

# define RESET		"\x1b[0m"
# define BOLD		"\x1b[1m"
# define BLACK		"\x1b[40m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[37m"

template<class T>
class Array {
	private:
		T		*arr;
		size_t	_size;
	public:
		Array();
		Array(unsigned int size);
		Array(const Array& other);
		~Array();
		Array&	operator=(const Array& other);
		T&		operator[](unsigned int n);

		size_t	size() const;
		void	printElements() const;
};

# include "Array.tpp"

#endif