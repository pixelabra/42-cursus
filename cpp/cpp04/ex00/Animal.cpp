#include "Animal.hpp"

Animal::Animal(): type("animaux")
{
	std::cout << "Animal default creation activated of type "<< type << ".\n";
}

Animal::Animal(std::string _type): type(_type)
{
	std::cout << "Animal type creation activated of type "<< type << ".\n";
}

Animal::Animal(const Animal& other): type(other.type)
{
	std::cout << "Animal copy constructor activated of type "<< type << ".\n";
}

Animal& Animal::operator=(const Animal& other)
{
	
	std::cout << "Animal assignment overload activated.\n";
	std::cout << "Animal of type " << this->getType() << " becomes of type " << other.getType() << ".\n\n";
	if (this != &other)
		type = other.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal of type " << type << " is no longer with us.\n";
}

void	Animal::makeSound(void) const
{
	std::cout << "wééééé\n";
}

std::string	Animal::getType() const { return (type); }
void		Animal::setType(std::string _type) {type = _type; }