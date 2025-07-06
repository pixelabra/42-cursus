/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:20:32 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/06 18:10:30 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>
# include <deque>

# define RESET		"\x1b[0m"
# define BOLD		"\x1b[1m"
# define BLACK		"\x1b[40m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[37m"

# include <cstdlib>

template <typename T, typename Container = std::deque<T> >
class MutantStack: public std::stack<T, Container> {
	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack& operator=(const MutantStack& other);
		~MutantStack();

		typedef typename std::stack<T, Container>::container_type::iterator 				iterator;
		typedef typename std::stack<T, Container>::container_type::reverse_iterator 		reverse_iterator;
		typedef typename std::stack<T, Container>::container_type::const_iterator			const_iterator;
		typedef typename std::stack<T, Container>::container_type::const_reverse_iterator	const_reverse_iterator;

		iterator				end();
		iterator				begin();
		reverse_iterator		rbegin();
		reverse_iterator		rend();
		const_iterator			begin() const;
		const_iterator			end() const;
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;
};

template <typename T, typename Container>
void	printStack(MutantStack<T, Container> mstack) {
	for (typename MutantStack<T, Container>::iterator it = mstack.begin(); it != mstack.end(); it++) {
		std::cout << *it << std::endl;
	}
}

# include "MutantStack.tpp"

#endif