/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:50 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/10 01:09:42 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <exception>

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

	class GradeTooHighException: public std::exception
	{
		private:
			std::string	message;
		public:
			GradeTooHighException();
			~GradeTooHighException() throw();
			const char* what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			private:
			std::string	message;
			public:
			GradeTooLowException();
			~GradeTooLowException() throw();
			const char* what() const throw();
	};
};

std::ostream&	operator<<(std::ostream& stream, const Bureaucrat& bcrat);

#endif