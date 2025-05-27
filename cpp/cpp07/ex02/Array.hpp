/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:26:12 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/27 20:29:48 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template<class T>
class Array {
	private:
		T		*arr;
		size_t	size;
	public:
		Array();
		Array(unsigned int size);
		Array(const Array& other);
		~Array();
		Array&	operator=(const Array& other);
		T&		operator[](unsigned int n);

		size_t	size() const;
};

#endif