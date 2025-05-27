/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:28:45 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/27 20:34:52 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template<typename T>
Array<T>::Array() { return (NULL); }

template<typename T>
Array<T>::Array(unsigned int n) {
	arr = new T(n);
	for (size_t i = 0; i < size; i++) {
		arr[i] = T();
	}
}

template<typename T>
Array<T>::~Array() {
	
}
