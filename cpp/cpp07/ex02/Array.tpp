/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:28:45 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/05 18:00:45 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array(): _size(0) { arr = new T[_size]; }

template <typename T>
Array<T>::Array(unsigned int n): _size(n) {
	arr = new T[_size];
	for (size_t i = 0; i < _size; i++) {
		arr[i] = T();
	}
}

template <typename T>
Array<T>::Array(const Array& other): _size(other._size) {
	arr = new T[_size];
	for (size_t i = 0; i < _size; i++) {
		arr[i] = other.arr[i];
	}
}

template <typename T>
Array<T>&	Array<T>::operator=(const Array& other) {
	if (this != &other) {
		_size = other._size;
		if (this->arr) delete[] this->arr;
		arr = new T[_size];
		for (size_t i = 0; i < _size; i++) {
			arr[i] = other.arr[i];
		}
	}
	return (*this);
}

template <typename T>
T&	Array<T>::operator[](unsigned int n) {
	if (arr && n < _size) {
		return (arr[n]);
	}
	throw (std::out_of_range(BOLD RED "Subscript out of range." RESET));
}

template<typename T>
Array<T>::~Array() {
	if (arr) {
		delete[] arr;
	}
}

template <typename T>
size_t	Array<T>::size() const { return (_size); }

template <typename T>
void	Array<T>::printElements() const {
	for (size_t i = 0; i < _size; i++) {
		std::cout << arr[i] << std::endl;
	}
}

