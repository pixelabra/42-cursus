/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:34:50 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/06 19:30:45 by agodeanu         ###   ########.fr       */
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
			GradeTooHighException(): message("Grade is too high") {}
			const char* what() const noexcept { return (message.c_str()); }
	};
	class GradeTooLowException: public std::exception
	{
		private:
			std::string	message;
		public:
			GradeTooLowException(): message("Grade is too low") {}
			const char* what() const { return (message.c_str()); }
	};
};

#endif