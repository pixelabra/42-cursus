#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>

# define RED		"\x1b[31m"
# define RESET		"\x1b[0m"
# define BOLD		"\x1b[1m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"

class Animal
{
	protected:
		std::string	type;
	public:
		Animal();
		Animal(std::string type);
		Animal(const Animal& other);
		Animal& operator=(const Animal& other);
		virtual ~Animal();

		std::string		getType() const;
		void			setType(std::string _type);

		virtual void	makeSound(void) const;
};

#endif