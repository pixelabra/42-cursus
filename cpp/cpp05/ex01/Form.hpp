/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:27:29 by agodeanu          #+#    #+#             */
/*   Updated: 2025/04/29 15:33:32 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"

class Form
{
	private:
		const std::string	name;
		const int			minSign;
		const int			minExec;
		bool				isSigned;
	public:
		Form();
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		const int&		getMinSign() const;

		class GradeTooHighException: public std::exception
		{
			
		};
		class GradeTooHighException: public std::exception
		{
			
		};
};

#endif