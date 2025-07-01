/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:46:38 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/01 18:05:18 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# include <cstdlib>

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

template<typename T>
void	print_arr(const T& elem) {
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