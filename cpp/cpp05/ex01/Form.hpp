/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:27:29 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/01 17:24:06 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string	name;
		const int			minSign;
		const int			minExec;
		bool				isSigned;
	public:
		Form();
		Form(const std::string _name, const int _minSign, const int _minExec);
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		const bool&			getIsSigned() const;
		const int&			getMinSign() const;
		const int&			getMinExec() const;
		const std::string&	getName() const;

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

std::ostream&	operator<<(std::ostream& stream, const Form& form);

#endif