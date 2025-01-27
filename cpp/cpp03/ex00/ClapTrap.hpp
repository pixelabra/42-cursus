/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:00 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/28 01:54:43 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
	private:
		std::string		Name;
		unsigned int	HP;
		unsigned int	EP;
		unsigned int	ATK;
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap& other);
		ClapTrap&	operator=(const ClapTrap& other);
		~ClapTrap();

		std::string		getName(void) const;
		unsigned int	getHP(void) const;
		unsigned int	getEP(void) const;
		unsigned int	getATK(void) const;
		void			setName(std::string name);
		void			setHP(unsigned int hp);
		void			setEP(unsigned int ep);
		void			setATK(unsigned int atk);

		void			attack(const std::string& target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);
};

std::ostream&	operator<<(std::ostream& stream, const ClapTrap& other);

# endif