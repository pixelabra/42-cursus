/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:25:05 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/18 20:03:32 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int	main() {
	Data		ptr(12);
	uintptr_t	ptr_result = Serializer::serialize(&ptr);	
	Data		*compare_ptr = Serializer::deserialize(ptr_result);

	std::cout << ptr.nbr << std::endl;
	std::cout << &ptr << std::endl;
	std::cout << (*compare_ptr).nbr << std::endl;
	std::cout << &(*compare_ptr) << std::endl;
	return (0);
}
