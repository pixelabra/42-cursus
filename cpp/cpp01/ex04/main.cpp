/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:12:44 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/03 21:37:28 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstring>

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
	std::ofstream	out_file(((std::string)av[1] + ".replace").c_str());
	if (!out_file.is_open())
	{
		std::cout << "Output file did not get created successfully.\n";
		if (in_file.is_open())
			in_file.close();
		return (0);
	}

	std::string	temp_str;
	size_t	start;
	size_t	end;
	while (!in_file.eof())
	{
		getline(in_file, temp_str);
		// end = temp_str.find(av[2]);
		end = 0;
		start = 0;
		// if (end == temp_str.npos)
		// 	out_file << temp_str;
		// while (end != temp_str.npos)
		// {
		// 	out_file << temp_str.substr(start, end);
		// 	out_file << av[3];
		// 	end += strlen(av[2]);
		// 	start = temp_str.find(av[2], end);
		// 	if (start == temp_str.npos)
		// 		start = temp_str.length();
		// 	out_file << temp_str.substr(end, start);
		// 	end = temp_str.find(av[2], end);
		// }
		
		while (1)
		{
			end = temp_str.find(av[2], end);
			if (end == temp_str.npos)
			{
				if (start == 0)
					out_file << temp_str;
				break ;
			}
			out_file << temp_str.substr(start, end);
			out_file << av[3];
			end += strlen(av[2]);
			start = temp_str.find(av[2], end);
			if (start == temp_str.npos)
				start = temp_str.length();
			out_file << temp_str.substr(end, start);
		}
		if (!in_file.eof())
			out_file << std::endl;
	}
	in_file.close();
	out_file.close();
	return (0);
}
