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
		std::vector<std::pair<int, int> >	pairs;

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

		const std::vector<int>& getVect() const;	
		const std::list<int>& getList() const;	
};

bool	validateArguments(char **av);

template <typename T>
void printContainer(T& container) {
	typename T::const_iterator it = container.begin();
	while (it != container.end()) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

template <typename T>
bool isSorted(const T& container) {
    if (container.size() < 2) return true;
    typename T::const_iterator prev = container.begin();
    typename T::const_iterator it   = prev;
	++it;
    for (; it != container.end(); ++it, ++prev) {
        if (*it < *prev)
			return false;
    }
    return true;
}

#endif