/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:46:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/25 20:12:31 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# include <cstdlib>

template<typename T>
void	print_arr(T& elem) {
	std::cout << elem << std::endl;
}

template<typename T>
void	iter(T *arr, size_t length, void (*fn_ptr)(T&)) {
	for (size_t i = 0; i < length; i++) {
		fn_ptr(arr[i]);
	}
}

template<typename T>
void	iter(T *arr, size_t length, void (*fn_ptr)(const T&)) {
	for (size_t i = 0; i < length; i++) {
		fn_ptr(arr[i]);
	}
}

#endif