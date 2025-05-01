/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:27:29 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 01:30:50 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	private:
		const std::string	name;
		const int			minSign;
		const int			minExec;
		bool				isSigned;
	public:
		AForm();
		AForm(const std::string _name, const int _minSign, const int _minExec);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();

		const bool&			getIsSigned() const;
		const int&			getMinSign() const;
		const int&			getMinExec() const;
		virtual const std::string&	getName() const = 0;

		void				beSigned(Bureaucrat& brcrat);

		class GradeTooHighException: public std::exception
		{
			private:
				std::string	message;
			public:
				GradeTooHighException();
				GradeTooHighException(std::string _message);
				~GradeTooHighException() throw();
				const char	*what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			private:
				std::string	message;
			public:
				GradeTooLowException();
				GradeTooLowException(std::string _message);
				~GradeTooLowException() throw();
				const char	*what() const throw();
		};
};

std::ostream&	operator<<(std::ostream& stream, const AForm& form);

#endif