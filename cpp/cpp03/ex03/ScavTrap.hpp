#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap: virtual public ClapTrap
{
	protected:
		static const unsigned int	default_HP = 100;
		static const unsigned int	default_EP = 50;
		static const unsigned int	default_ATK = 20;
	public:
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap& other);
		ScavTrap&	operator=(const ScavTrap& other);
		~ScavTrap();

		void			guardGate(void);
		virtual void	attack(std::string& name);
};

#endif