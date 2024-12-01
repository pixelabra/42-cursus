/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codebeauty.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:50:41 by agodeanu          #+#    #+#             */
/*   Updated: 2024/11/27 01:44:22 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class	AbstractEmployee
{
	virtual void	AskForPromotion() = 0;
};

class	Employee: AbstractEmployee
{
	private:
		std::string	Company;
		int			Age;

	protected:
		std::string	Name;

	public:
		void		setName(std::string name) {
			Name = name;
		}
		std::string	getName() {
			return Name;
		}
		void		setCompany(std::string company) {
			Company = company;
		}
		std::string	getCompany() {
			return Company;
		}
		void		setAge(int age) {
			if (age >= 38)
				Age = age;
		}
		int	getAge() {
			return Age;
		}
		void		IntroduceYourself() {
			std::cout << "Name - " << Name << std::endl;
			std::cout << "Company - " << Company << std::endl;
			std::cout << "Age - " << Age << std::endl;
		}
   
		Employee(std::string name, std::string company, int age) {
			Name = name;
			Company = company;
			Age = age;
		}
		void	AskForPromotion() {
			if (Age > 30)
				std::cout << Name << " got promoted!" << std::endl;
			else
				std::cout << Name << ", sorry NO promotion for you!" << std::endl;
		}
		virtual void	Work() {
			std::cout << Name << " is checking email, task backlog, performing tasks..." << std::endl;
		}
};

class	Developer: public Employee
{
	public:
		std::string	FavProgrammingLanguage;
		Developer(std::string name, std::string company, int age, std::string favprogramminglanguage)
			: Employee(name, company, age)
		{
			FavProgrammingLanguage = favprogramminglanguage;
		}
		void	FixBug() {
			std::cout << getName() << " fixed bug using " << FavProgrammingLanguage << std::endl;
		}
		void	Work() {
			std::cout << Name << " is writing " << FavProgrammingLanguage << " code" << std::endl;
		}
};

class	Teacher: public Employee
{
	public:
		std::string	Subject;
		void	PrepareLesson() {
			std::cout << Name << " is preparing " << Subject << " lesson" << std::endl;
		}
		Teacher(std::string name, std::string company, int age, std::string subject)
			: Employee(name, company, age)
			{
				Subject = subject;
			}
		void	Work() {
			std::cout << Name << " is teaching " << Subject << std::endl;
		}
};

int	main()
{
	Employee	employee1 = Employee("Saldina", "YT-CodeBeauty", 25);
	Employee	employee2 = Employee("John", "Amazon", 35);
	Developer	dev = Developer("Saldina", "YT-CodeBeauty", 25, "C++");
	Teacher		teach = Teacher("Jack", "Ccool School", 35, "History");
	Employee	*e1 = &dev;
	Employee	*e2 = &teach;

	employee1.IntroduceYourself();
	employee2.IntroduceYourself();

	employee1.setAge(18);
	std::cout << employee1.getName() << " is " << employee1.getAge() << " years." << std::endl;
	employee1.AskForPromotion();
	employee2.AskForPromotion();
	dev.FixBug();
	dev.AskForPromotion();
	teach.PrepareLesson();
	teach.AskForPromotion();
	// dev.Work();
	// teach.Work();
	e1->Work();
	e2->Work();
}
