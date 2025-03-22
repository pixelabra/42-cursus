#include "Animal.hpp"

Animal::Animal(): type("animaux")
{
	std::cout << "Animal default creation activated\n";
}

Animal::Animal(std::string _type): type(_type)
{
	std::cout << "Animal type creation activated\n";
}

Animal::Animal(const Animal& other): type(other.type)
{
	std::cout << "Animal copy constructor activated\n";
}

Animal& Animal::operator=(const Animal& other)
{
	if (this == &other)
		return (*this);
	type = other.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal is no longer with us.\n";
}

std::string	Animal::getType() const { return (type);}