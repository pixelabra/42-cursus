/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:45:35 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/25 20:12:20 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "iter.hpp"

int	main() {
	size_t	ARR_SIZE = 10;
	int		arr[ARR_SIZE];
	void	(*fn_ptr)(int&) = print_arr;

	srand(time(0));
	for (size_t i = 0; i < ARR_SIZE; i++) {
		arr[i] = rand();
	}
	::iter(arr, ARR_SIZE, fn_ptr);

	return (0);
}
