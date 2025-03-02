#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal creation activated\n";
}

Animal::Animal(std::string type)
{
	std::cout << "Animal type creation activated\n";
	this->type = type;
}

Animal::Animal(const Animal& other)
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

