/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:21:14 by agodeanu          #+#    #+#             */
/*   Updated: 2025/03/28 15:31:19 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include "ICharacter.hpp"

class AMateria
{
	protected:
		std::string	type;
	public:
		AMateria();
		AMateria(std::string const &_type);
		AMateria(const AMateria& other);
		AMateria& operator=(const AMateria& other);
		virtual ~AMateria();

		std::string const &getType() const;
		virtual AMateria *clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif