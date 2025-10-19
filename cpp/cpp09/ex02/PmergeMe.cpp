/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:14:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/10/19 23:47:29 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

double  getTimeInMicroseconds() {
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1) {
		throw std::runtime_error("Gettimeofday failed");
	}
	return (t.tv_sec * 1000000 + t.tv_usec);
}

bool	validateArguments(char **av) {
	for (size_t i = 1; av[i]; i++) {
		for(size_t j = 0; av[i][j]; j++) {
			if (!isdigit(av[i][j])) 
				return false;
		}
	}
	return true;
}

template <typename T>
typename T::iterator itAt(T& c, size_t n) {
    typename T::iterator it = c.begin();
    while (n-- && it != c.end())
        ++it;
    return it;
}

template <typename T>
int valueAt(const T& c, size_t n) {
    typename T::const_iterator it = c.begin();
    while (n-- && it != c.end())
        ++it;
    return (it == c.end()) ? -1 : *it;
}

template <typename T>
size_t findIndexOf(const T& c, int needle) {
    size_t idx = 0;
    for (typename T::const_iterator it = c.begin(); it != c.end(); ++it, ++idx) {
        if (*it == needle)
            return idx;
    }
    return c.size();
}

template <typename T>
static void binaryInsert(T& container, int value, size_t end) {
    if (end > container.size()) end = container.size();

    typename T::iterator first = container.begin();
    size_t count = end;

    while (count > 0) {
        size_t step = count / 2;

        typename T::iterator mid = first;
        for (size_t i = 0; i < step; ++i)
			++mid;

        if (*mid < value) {
            ++mid;
            first = mid;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    container.insert(first, value);
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other): vect(other.vect), lst(other.lst) {}

PmergeMe::PmergeMe(char **av) {
	checkDuplicates(av);
	populateContainers(av);
	sortVector();
	sortList();
}

PmergeMe	PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		vect = other.vect;
		lst = other.lst;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

const std::vector<int>& PmergeMe::getVect() const { return (vect); }

const std::list<int>& PmergeMe::getList() const { return (lst); }

void	PmergeMe::checkDuplicates(char **av) {
	std::set<int>	set;

	for (size_t i = 1; av[i]; i++) {
		long numb = std::atol(av[i]);
		if (numb > std::numeric_limits<int>::max())
			throw std::invalid_argument("Number should not be greater than INT_MAX");
		std::set<int>::iterator it = set.find(numb);
		if (it != set.end()) {
			throw std::invalid_argument("No duplicates allowed");
		}
		set.insert(numb);
	}
}

void	PmergeMe::populateContainers(char **av) {
	double startTime, endTime;
	
	startTime = getTimeInMicroseconds();
	for (size_t i = 1; av[i]; i++) {
		int numb = std::atoi(av[i]);
		vect.push_back(numb);
	}
	endTime = getTimeInMicroseconds();
	std::cout << "This much time to populate vector: "
			<< std::fixed << std::setprecision(2)
			<< (endTime - startTime) << "us" << std::endl;
	
	startTime = getTimeInMicroseconds();
	for (size_t i = 1; av[i]; i++) {
		int numb = std::atoi(av[i]);
		lst.push_back(numb);
	}
	endTime = getTimeInMicroseconds();
	std::cout << "This much time to populate list: "
			<< std::fixed << std::setprecision(2)
			<< (endTime - startTime) << "us" << std::endl;
}

std::vector<int>	generateJacobsthal(size_t contSize) {
    std::vector<int>	jacobsthal;

	if (!contSize)
        return (jacobsthal);
    jacobsthal.push_back(1);
    if (contSize == 1)
        return (jacobsthal);
    jacobsthal.push_back(1);
    size_t prev2 = 1, prev1 = 1;
    while (true) {
        size_t next = prev1 + 2 * prev2;
        if (next > contSize)
            break ;
        jacobsthal.push_back(next);
        prev2 = prev1;
        prev1 = next;
    }
    return (jacobsthal);
}

template<typename T>
void	PmergeMe::handlePairing(const T& container) {
	pairs.clear();
	typename T::const_iterator it = container.begin();
	while (it != container.end()) {
		typename T::const_iterator it_next = it;
		it_next++;
		
		if (it_next == container.end())
		break ;
		if (*it < *it_next)
			pairs.push_back(std::make_pair(*it_next, *it));
		else
			pairs.push_back(std::make_pair(*it, *it_next));
		it = it_next;
		++it;
	}
	std::sort(pairs.begin(), pairs.end());
}

void	PmergeMe::sortVector() {
	if (vect.size() <= 1 || isSorted(vect)) {
		std::cout << "Vector already sorted!" << std::endl;
		return ;
	}
	double startTime = getTimeInMicroseconds();
	handlePairing(vect);

	std::vector<int>	main;
	std::vector<int>	pend;

	for (size_t i = 0; i < pairs.size(); i++) {
		main.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}
	main.insert(main.begin(), pend.front());
	pend.erase(pend.begin());
	std::vector<int>	jacobsthalVect = generateJacobsthal(pend.size());
	std::vector<bool>	inserted(pend.size(), false);
	for (size_t i = 0; i < jacobsthalVect.size(); ++i) {
		size_t start = (i > 0) ? static_cast<size_t>(jacobsthalVect[i - 1]) : 0;
		size_t top = static_cast<size_t>(jacobsthalVect[i] - 1);
		for (size_t jIndex = top; jIndex >= start && jIndex < pend.size(); --jIndex) {
			if (!inserted[jIndex]) {
				int first = pairs[jIndex + 1].first;
                size_t end = findIndexOf(main, first);

                int val = valueAt(pend, jIndex);
				binaryInsert(main, val, end);
				inserted[jIndex] = true;
			}
			if (jIndex == 0)
				break ;
		}
	}
	for (size_t i = 0; i < pend.size(); i++) {
		if (!inserted[i])
		binaryInsert(main, pend[i], main.size());
	}
	if (vect.size() % 2)
		binaryInsert(main, vect[vect.size() - 1], main.size());
	vect = main;
	double endTime = getTimeInMicroseconds();
	std::cout << "This much time to sort vector: "
			<< std::fixed << std::setprecision(2)
			<< (endTime - startTime) << "us" << std::endl;
}

void PmergeMe::sortList() {
    if (lst.size() <= 1 || isSorted(lst)) {
        std::cout << "List already sorted!" << std::endl;
        return;
    }
    double startTime = getTimeInMicroseconds();
    handlePairing(lst);

    std::list<int> main;
    std::list<int> pend;

    for (size_t i = 0; i < pairs.size(); ++i) {
        main.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
	main.insert(main.begin(), pend.front());
	pend.pop_front();
    std::vector<int> jacobsthalVect = generateJacobsthal(pend.size());
    std::vector<bool> inserted(pend.size(), false);

	for (size_t i = 0; i < jacobsthalVect.size(); ++i) {
        size_t start = (i > 0) ? static_cast<size_t>(jacobsthalVect[i - 1]) : 0;
        size_t top   = static_cast<size_t>(jacobsthalVect[i] - 1);

        for (size_t jIndex = top; jIndex >= start && jIndex < pend.size(); --jIndex) {
            if (!inserted[jIndex]) {
                int first = pairs[jIndex + 1].first;
                size_t end = findIndexOf(main, first);

                int val = valueAt(pend, jIndex);
                binaryInsert(main, val, end);
                inserted[jIndex] = true;
            }
            if (jIndex == 0)
				break ;
        }
    }
    for (size_t j = 0; j < inserted.size(); ++j) {
        if (!inserted[j]) {
            int val = valueAt(pend, j);
            binaryInsert(main, val, main.size());
        }
    }
    if (lst.size() % 2)
        binaryInsert(main, lst.back(), main.size());
    lst = main;
    double endTime = getTimeInMicroseconds();
    std::cout << "This much time to sort list: "
              << std::fixed << std::setprecision(2)
              << (endTime - startTime) << "us" << std::endl;
}
