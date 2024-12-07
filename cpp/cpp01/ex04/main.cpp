/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:12:44 by agodeanu          #+#    #+#             */
/*   Updated: 2024/12/07 18:44:24 by agodeanu         ###   ########.fr       */
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
	outf.open(((std::string)av[1] + ".replace").c_str());
	if (!outf.is_open())
	{
		std::cout << WR_OUTF;
		if (inf.is_open())
			inf.close();
		return (0);
	}
	return (1);
}

void	search_and_replace(char **av, std::ifstream &inf, std::ofstream &outf)
{
	size_t			start;
	size_t			end;
	std::string		temp_str;

	while (getline(inf, temp_str))
	{
		start = 0;
		while (1)
		{
			end = temp_str.find(av[2], start);
			if (end == temp_str.npos)
			{
				end = temp_str.length();
				outf << temp_str.substr(start, end - start);
				break ;
			}
			outf << temp_str.substr(start, end - start);
			outf << av[3];
			start = end + strlen(av[2]);
		}
		if (!inf.eof())
			outf << std::endl;
	}
}

int	main(int ac, char **av)
{
	std::ifstream	inf;
	std::ofstream	outf;

	if (!open_files(ac, av, inf, outf))
		return (0);
	search_and_replace(av, inf, outf);
	inf.close();
	outf.close();
	return (0);
}
