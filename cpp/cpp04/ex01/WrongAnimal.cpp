#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): type("animaux")
{
	std::cout << "WrongAnimal default creation activated\n";
}

WrongAnimal::WrongAnimal(std::string _type): type(_type)
{
	std::cout << "WrongAnimal type creation activated\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other): type(other.type)
{
	std::cout << "WrongAnimal copy constructor activated\n";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (this == &other)
		return (*this);
	type = other.type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal is no longer with us.\n";
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "wééééé\n";
}

std::string	WrongAnimal::getType() const { return (type);}