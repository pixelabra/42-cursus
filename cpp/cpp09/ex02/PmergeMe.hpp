#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <algorithm>
# include <exception>
# include <cstring>
# include <set>
# include <ctime>
# include <limits>
# include <list>
# include <vector>
# include <iomanip>
# include <sys/time.h>

class PmergeMe {
	private:
		std::vector<int>					vect;
		std::list<int>						lst;
		std::vector<std::pair<int, int> >	pair;

		void	populateContainers(char **av);
		void	checkDuplicates(char **av);
		void	sortVector();
		void	sortList();
		
		template<typename T>
		void	handlePairing(const T& container);
	public:
		PmergeMe();
		PmergeMe(char **av);
		PmergeMe(const PmergeMe& other);
		PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		void	printVector() const;
		void	printList() const;
		

};

bool	validateArguments(char **av);

#endif