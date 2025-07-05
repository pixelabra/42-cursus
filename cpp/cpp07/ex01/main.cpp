/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:45:35 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/05 17:16:04 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "iter.hpp"

class Array {
	public:
		static const size_t			arrSize = 3;
	
		static const unsigned int	*getArrayConst() { 
		unsigned int	*arr = new unsigned int[arrSize];
			for (unsigned int i = 0; i < arrSize; i++) {
				arr[i] = rand();
			}
			return (arr);
		};
};

int	main() {
	srand(time(0));
	{
		int		arr[Array::arrSize];
		void	(*fn_ptr)(const int&) = print_arr;

		for (size_t i = 0; i < Array::arrSize; i++) {
			arr[i] = rand();
		}
		::iter(arr, Array::arrSize, fn_ptr);
		std::cout << BLUE "CONST" << RESET << std::endl;
		const int	*data = arr;
		::iter(data, Array::arrSize, fn_ptr);
	}
	std::cout << BOLD RED << "INTERMISSION" << RESET << std::endl;
	{
		const unsigned int	*array = Array::getArrayConst();
		const unsigned int	*array2 = Array::getArrayConst();
		void	(*fn_ptr)(const unsigned int&) = print_arr;
		size_t	size = Array::arrSize;

		::iter(array, size, fn_ptr);
		std::cout << MAGENTA << "TESTING" RESET << std::endl;
		::iter(array2, size, fn_ptr);

		delete[] array;
		delete[] array2;
	}
	return (0);
}
