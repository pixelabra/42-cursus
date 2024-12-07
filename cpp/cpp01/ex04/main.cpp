/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:12:44 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/05 20:22:49 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstring>

# define WR_INPUT	"Invalid input.\n./sed <filename> string1 string2\n"
# define WR_INF		"Input file did not open successfully. Do better!\n"
# define WR_OUTF	"Output file did not get created successfully.\n"

int	open_files(int ac, char **av, std::ifstream &inf, std::ofstream &outf)
{
	if (ac != 4)
	{
		std::cout << WR_INPUT;
		return (0);
	}
	inf.open(av[1]);
	if (!inf.is_open())
	{
		std::cout << WR_INF;
		return (0);
	}
	outf.open(((std::string)av[2] + ".replace").c_str());
	if (!outf.is_open())
	{
		std::cout << WR_OUTF;
		if (inf.is_open())
			inf.close();
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	std::ifstream	inf;
	std::ofstream	outf;

	if (!open_files(ac, av, inf, outf));
		return (0);
	
}


// int	main(int ac, char **av)
// {
// 	if (ac != 4)
// 	{
// 		std::cout << "Invalid input.\n./sed <filename> string1 string2\n";
// 		return (0);
// 	}
// 	std::ifstream	in_file(av[1]);
// 	if (!in_file.is_open())
// 	{
// 		std::cout << "Input file did not open successfully. Do better!\n";
// 		return (0);
// 	}
// 	std::ofstream	out_file(((std::string)av[1] + ".replace").c_str());
// 	if (!out_file.is_open())
// 	{
// 		std::cout << "Output file did not get created successfully.\n";
// 		if (in_file.is_open())
// 			in_file.close();
// 		return (0);
// 	}
// 	std::string	temp_str;
// 	size_t	start;
// 	size_t	end;
// 	while (!in_file.eof())
// 	{
// 		getline(in_file, temp_str);
// 		// end = temp_str.find(av[2]);
// 		end = 0;
// 		start = 0;
// 		// if (end == temp_str.npos)
// 		// 	out_file << temp_str;
// 		// while (end != temp_str.npos)
// 		// {
// 		// 	out_file << temp_str.substr(start, end);
// 		// 	out_file << av[3];
// 		// 	end += strlen(av[2]);
// 		// 	start = temp_str.find(av[2], end);
// 		// 	if (start == temp_str.npos)
// 		// 		start = temp_str.length();
// 		// 	out_file << temp_str.substr(end, start);
// 		// 	end = temp_str.find(av[2], end);
// 		// }
		
// 		while (1)
// 		{
// 			end = temp_str.find(av[2], end);
// 			if (end == temp_str.npos)
// 			{
// 				if (start == 0)
// 					out_file << temp_str;
// 				break ;
// 			}
// 			out_file << temp_str.substr(start, end);
// 			out_file << av[3];
// 			end += strlen(av[2]);
// 			start = temp_str.find(av[2], end);
// 			if (start == temp_str.npos)
// 				start = temp_str.length();
// 			out_file << temp_str.substr(end, start);
// 		}
// 		if (!in_file.eof())
// 			out_file << std::endl;
// 	}
// 	in_file.close();
// 	out_file.close();
// 	return (0);
// }
