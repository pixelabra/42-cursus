/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:27:32 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/24 20:26:16 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>

template<typename T>
void	swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
T	min(const T a, const T b) {
	if (a < b) {
		return (a);
	}
	return (b);
}

template<typename T>
T	max(const T a, const T b) {
	if (a > b) {
		return (a);
	}
	return (b);
}

#endif