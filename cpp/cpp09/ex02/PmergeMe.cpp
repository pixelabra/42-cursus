/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:14:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/10/13 00:01:55 by agodeanu         ###   ########.fr       */
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

void	PmergeMe::printList() const {
	
}

void	PmergeMe::printVector() const {
	
}

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
	for (size_t i = 0; i < container.size(); i += 2) {
		if (i > container.size() - 1) {
			if (container[i] > container[i + 1])
				pair.push_back(std::make_pair(container[i], conatiner[i + 1]));
			else
				pair.push_back(std::make_pair(container[i + 1], conatiner[i]));
		}
	}
}

void	PmergeMe::sortVector() {
	double startTime, endTime;
	
	if (vect.size() <= 1 || isSorted(vect)) {
		std::cout << "Vector already sorted!" << std::endl;
		return ;
	}
	startTime = getTimeInMicroseconds();
	
	
}

void	PmergeMe::sortList() {

}

template <typename T>
static bool	isSorted(const T& container) {
	for (size_t i = 1; i < container.size(); i++) {
		if (container[i - 1] > container[i])
			return false;
	}
	return true;
}
