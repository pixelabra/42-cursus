/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:06:56 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/18 20:24:41 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <cstdlib>
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"

class Base {
	public:
		virtual	~Base();
};

Base	*generate(void);
void	identify(Base *p);
void	identify(Base& p);

#endif