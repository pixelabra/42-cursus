/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:50 by agodeanu          #+#    #+#             */
/*   Updated: 2025/05/02 00:43:26 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <exception>
# include "AForm.hpp"

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

class AForm;

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat&		operator=(const Bureaucrat& other);
		virtual ~Bureaucrat();

		const std::string&		getName() const;
		const int&				getGrade() const;

		void					promote();
		void					demote();
		void					signForm(AForm& frm);

	class GradeTooHighException: public std::exception
	{
		private:
			std::string	message;
		public:
			GradeTooHighException();
			GradeTooHighException(std::string _message);
			~GradeTooHighException() throw();
			const char* what() const throw();
	};
	class GradeTooLowException: public std::exception
	{
		private:
			std::string	message;
		public:
			GradeTooLowException();
			GradeTooLowException(std::string _message);
			~GradeTooLowException() throw();
			const char* what() const throw();
	};
};

std::ostream&	operator<<(std::ostream& stream, const Bureaucrat& bcrat);

#endif