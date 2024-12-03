/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:12:44 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/03 19:07:20 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << "Invalid input.\n./sed <filename> string1 string2\n";
		return (0);
	}

	std::ifstream	in_file(av[1]);
	if (!in_file.is_open())
	{
		std::cout << "Input file did not open successfully. Do better!\n";
		return (0);
	}
	std::ofstream	out_file((std::string)av[1] + ".replace");
	if (!out_file.is_open())
	{
		std::cout << "Output file did not get created successfully.\n";
		return (0);
	}
	std::string	temp_str;
	while (1)
	{
		getline(in_file, temp_str);
		out_file << temp_str;
		std::cout << temp_str;
		if (!in_file.eof())
			out_file << std::endl;
		else
			break ;
	}
	in_file.close();
	out_file.close();
	return (0);
}
