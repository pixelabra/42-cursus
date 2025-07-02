/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:20:32 by agodeanu          #+#    #+#             */
/*   Updated: 2025/07/02 19:43:09 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>
# include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack: public std::stack<T, Container> {
	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack& operator=(const MutantStack& other);
		~MutantStack();

		typedef typename std::stack<T, Container>::container_type::iterator 		iterator;
		typedef typename std::stack<T, Container>::container_type::const_iterator	const_iterator;

		iterator		end();
		iterator		begin();
		iterator		rbegin();
		iterator		rend();
		const_iterator	begin() const;
		const_iterator	end() const;
		const_iterator	rbegin() const;
		const_iterator	rend() const;
};

# include "MutantStack.tpp"

#endif