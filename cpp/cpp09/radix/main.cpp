/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:32:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/09 14:54:47 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Radix.hpp"

unsigned int	computeBits(unsigned int maxVal) {
	unsigned int	bits = 0;
	while (maxVal > 0) {
		++bits;
		maxVal >>= 1;
	}
	return (bits);
}

std::vector<int>& radix(std::vector<int>& arr, unsigned int r) {
    std::vector<int> negatives;
    std::vector<int> positives;

    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] < 0)
            negatives.push_back(-arr[i]);
        else
            positives.push_back(arr[i]);
    }
    if (!negatives.empty()) {
        unsigned int maxNeg = *std::max_element(negatives.begin(), negatives.end());
        unsigned int nBitsNeg = computeBits(maxNeg);
        sortRadix(negatives, nBitsNeg, r);
    }
    if (!positives.empty()) {
        unsigned int maxPos = *std::max_element(positives.begin(), positives.end());
        unsigned int nBitsPos = computeBits(maxPos);
        sortRadix(positives, nBitsPos, r);
    }
    arr.clear();
    for (size_t i = negatives.size(); i-- > 0; )
        arr.push_back(-negatives[i]);
    arr.insert(arr.end(), positives.begin(), positives.end());
    return (arr);
}

void	sortRadix(std::vector<int>& arr, unsigned int nBits, unsigned int r) {
	unsigned int mask = (1 << r) - 1;

	for (unsigned int bitPos = 0; bitPos < nBits; bitPos += r) {
		std::vector< std::vector<int> >	buckets(1 << r);

		for (size_t i = 0; i < arr.size(); i++) {
			unsigned int digit = (static_cast<unsigned int>(arr[i]) >> bitPos) & mask;
			buckets[digit].push_back(arr[i]);
		}
		arr.clear();
		for (size_t b = 0; b < buckets.size(); b++) {
			arr.insert(arr.end(), buckets[b].begin(), buckets[b].end());
		}
	}
}

int	main() {
	std::vector<int>	arr;
	std::vector<int>	sorted;

	srand(time(0));
	fillIt(arr, 100, 99);
	printContainer(arr);
	sorted = radix(arr, 8);

	std::cout << MAGENTA BOLD << "TAU" << RESET << std::endl;
	printContainer(sorted);
	return (0);
}
