/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:30:36 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/04 17:57:27 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "ShrubberyCreationForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"

class Intern
{
	public:	
		Intern();
		Intern(const Intern& other);
		Intern&	operator=(const Intern& other);
		~Intern();

		AForm	*makeForm(std::string formName, std::string targetForm) const;

		class FormCreationFailedException: public std::exception
		{
			private:
				std::string	message;
			public:
				FormCreationFailedException(std::string _message);
				~FormCreationFailedException() throw();
				const char*	what() const throw();
		};
};

#endif