/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:56:25 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 15:56:12 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <iostream>
# include "AMateria.hpp"
# include "Ice.hpp"
# include "Cure.hpp"

# define INV	4
class ICharacter
{
	protected:
		std::string	name;
		AMateria	*inventory[INV];
	public:
		ICharacter();
		ICharacter(const ICharacter& other);
		ICharacter(const std::string _name);
		ICharacter& operator=(const ICharacter& other);
		virtual ~ICharacter();

		virtual std::string const &getName() const = 0;
		virtual void equip(AMateria *m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

#endif