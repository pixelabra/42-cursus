#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
	protected:
		static const unsigned int	default_HP = 100;
		static const unsigned int	default_EP = 100;
		static const unsigned int	default_ATK = 30;
	public:
		FragTrap();
		FragTrap(std::string name);
		FragTrap(const FragTrap& other);
		FragTrap&	operator=(const FragTrap& other);
		~FragTrap();

		void	highFivesGuys();
};

#endif